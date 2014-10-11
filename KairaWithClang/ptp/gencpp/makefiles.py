#
#    Copyright (C) 2012 Stanislav Bohm
#
#    This file is part of Kaira.
#
#    Kaira is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, version 3 of the License, or
#    (at your option) any later version.
#
#    Kaira is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Kaira.  If not, see <http://www.gnu.org/licenses/>.
#

import base.utils
import base.paths as paths
import os.path

def create_makefile_config():
    return {
            "libs" : [],
            "libdir" : [],
            "include" : []
    }

def kaira_path(path):
    return os.path.join("${KAIRA_PATH}", path)

def prepare_makefile(project, config, directory):

    def add_prefix(prefix, value):
        if not value.startswith(prefix):
            return prefix + value
        return value

    import ptp
    if config is None:
        config = create_makefile_config()

    if project.get_build_with_octave():
        config["include"].append(kaira_path(paths.CAOCTAVE_INCLUDE_DIR))
        config["include"].append(ptp.get_config("Octave", "INCFLAGS"))
        config["libdir"].append(ptp.get_config("Octave", "LFLAGS"))
        config["libs"].append(ptp.get_config("Octave", "LIBS"))

    makefile = base.utils.Makefile()
    makefile.set_top_comment("This file is autogenerated.\n"
                                "Do not edit directly this file.")
    makefile.set("KAIRA_PATH", paths.KAIRA_ROOT)
    makefile.set("CXX", ptp.config.get("Main", "CXX"))
    makefile.set("CFLAGS", project.get_build_option("CFLAGS"))

    makefile.set("INCLUDE",
                 "-I{0} -I{1} {2}".format(
                     kaira_path(paths.CAILIE_INCLUDE_DIR),
                     os.path.relpath(project.root_directory, directory),
                     " ".join(add_prefix("-I", s) for s in config["include"])))

    makefile.set("LIBDIR",
                 "-L{0} {1}".format(kaira_path(paths.CAILIE_LIB_DIR),
                                    " ".join(add_prefix("-L", s) for s in config["libdir"])))
    makefile.set("LIBS",
                 project.get_build_option("LIBS") + " "
                 + " ".join(add_prefix("-l", s) for s in config["libs"])
                 + " -lcailie -lpthread -lrt ")

    if ptp.config.has_option("Main", "MPICXX"):
        mpicxx = ptp.config.get("Main", "MPICXX")
    else:
        mpicxx = "mpic++"
    makefile.set("MPICXX", mpicxx)

    makefile.set("MPILIBS",
                 project.get_build_option("LIBS") + " "
                 + " ".join(add_prefix("-l", s) for s in config["libs"])
                 + " -lcailiempi -lpthread -lrt ")

    makefile.rule(".cpp.o", [], "$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@")
    makefile.rule(".cc.o", [], "$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@")
    makefile.rule(".c.o", [], "$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@")

    return makefile

def get_other_dependancies(project, directory):
    d = os.path.relpath(project.get_root_directory(), directory)
    if project.get_build_option("OTHER_FILES"):
        return [ os.path.join(d, os.path.splitext(f)[0] + ".o")
                 for f in project.get_build_option("OTHER_FILES").split("\n") ]
    else:
        return []

def prepare_program_makefile(project, config, directory, other_files=None):
    makefile = prepare_makefile(project, config, directory)

    name = project.get_name()
    name_o = name + ".o"
    name_cpp = name + ".cpp"

    deps = [ name_o ] + get_other_dependancies(project, directory)

    if other_files is None:
        other_files = []

    makefile.rule("all", [ name ], phony=True)
    makefile.rule(name,
                  deps,
                  "$(CXX) " + " ".join(deps) + " -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(LIBS) ")
    makefile.rule(name_o,
                  [ name_cpp ],
                  "$(CXX) $(CFLAGS) $(INCLUDE) -c {0} -o {1}".format(name_cpp, name_o))
    makefile.rule("clean",
                  [],
                  "rm -f {0} {1}".format(name, " ".join(deps + list(other_files))), phony=True)
    return makefile


def write_statespace_makefile(project, directory):
    config = create_makefile_config()
    config["include"].append(kaira_path(paths.CAVERIF_INCLUDE_DIR))
    config["libdir"].append(kaira_path(paths.CAVERIF_LIB_DIR))
    config["libs"].append("caverif")
    config["libs"].append("mhash")
    makefile = prepare_program_makefile(project, config, directory)
    makefile.write_to_file(os.path.join(directory, "makefile"))

def write_simrun_makefile(project, directory):
    config = create_makefile_config()
    config["include"].append(kaira_path(paths.CASIMRUN_INCLUDE_DIR))
    config["libdir"].append(kaira_path(paths.CASIMRUN_LIB_DIR))
    config["libs"].append("casimrun")
    makefile = prepare_program_makefile(project, config, directory)
    makefile.write_to_file(os.path.join(directory, "makefile"))

def write_program_makefile(project, directory):
    name = project.get_name()
    name_cpp = name + ".cpp"
    name_mpi = name + "_mpi"
    name_mpi_o = name + "_mpi.o"
    other_files = [ name_mpi, name_mpi_o ]
    makefile = prepare_program_makefile(project, None, directory, other_files)

    makefile.rule("mpi", [ name_mpi ], phony=True)

    other_deps = get_other_dependancies(project, directory)
    deps_mpi = [ name_mpi_o ] + other_deps

    makefile.rule(name_mpi, deps_mpi, "$(MPICXX) -D CA_MPI " + " ".join(deps_mpi)
        + " -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(MPILIBS)" )
    makefile.rule(name_mpi_o, [ name_cpp ],
        "$(MPICXX) -DCA_MPI $(CFLAGS) $(INCLUDE) -c {0} -o {1}".format(name_cpp, name_mpi_o))
    makefile.write_to_file(os.path.join(directory, "makefile"))

def write_server_makefile(project, directory):

    config = create_makefile_config()
    config["include"].append(kaira_path(paths.CASERVER_INCLUDE_DIR))
    config["libdir"].append(kaira_path(paths.CASERVER_LIB_DIR))
    config["libs"].append("caserver")

    makefile = prepare_makefile(project, config, directory)

    name = project.get_name() + "_server"
    name_cpp = name + ".cpp"
    name_o = name + ".o"

    name_mpi = project.get_name() + "_server_mpi"
    name_mpi_o = name_mpi + ".o"

    makefile.rule("all", [ name ], phony = True)
    makefile.rule("mpi", [ name_mpi ], phony = True)

    other_deps = get_other_dependancies(project, directory)
    deps = [ name_o ] + other_deps
    deps_mpi = [ name_mpi_o ] + other_deps

    makefile.rule(name, deps, "$(CXX) " + " ".join(deps) +
        " -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(LIBS)" )

    makefile.rule(name_mpi, deps_mpi, "$(MPICXX) " + " ".join(deps_mpi) +
        " -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(MPILIBS)" )

    makefile.rule(name_o, [ name_cpp ],
        "$(CXX) $(CFLAGS) $(INCLUDE) -c {0} -o {1}".format(name_cpp, name_o))

    makefile.rule(name_mpi_o, [ name_cpp ],
        "$(MPICXX) -DCA_MPI $(CFLAGS) $(INCLUDE) -c {0} -o {1}".format(name_cpp, name_mpi_o))

    makefile.rule("clean", [], "rm -f {0} {0}_mpi {0}_mpi.o {1}".format(name," ".join(deps)))
    makefile.write_to_file(os.path.join(directory, "makefile"))

def write_library_makefile(project, directory, rpc=False):

    config = create_makefile_config()

    if rpc:
        config["include"].append(kaira_path(paths.CACLIENT_INCLUDE_DIR))
        config["libdir"].append(kaira_path(paths.CACLIENT_LIB_DIR))
        config["libs"].append("caclient")


    makefile = prepare_makefile(project, config, directory)
    other_deps = get_other_dependancies(project, directory)

    name = project.get_name()
    name_o = name + ".o"
    name_cpp = name + ".cpp"
    name_mpi_o = name + "_mpi.o"
    libname_a = "lib{0}.a".format(name)
    libname_mpi_a = "lib{0}_mpi.a".format(name)

    targets = [ libname_a ]

    if rpc:
        # In rpc mode we are compiling only frontend so
        # there ale always libname_a even for MPI
        targets = [ libname_a, "server" ]
        targets_mpi = [ libname_a, "server-mpi" ]
    else:
        targets = [ libname_a ]
        targets_mpi = [ libname_mpi_a ]

    if project.library_octave:
        targets.append("octave")
        targets_mpi.append("octave")

    makefile.rule("all", targets, phony = True)
    makefile.rule("mpi", targets_mpi, phony = True)

    if project.library_octave:
        name_oct = name + ".oct"
        name_oct_cpp = name + "_oct.cpp"
        makefile.rule("octave", [ name_oct ], phony = True)
        makefile.rule(name_oct,
                      [ name_oct_cpp ],
                      "mkoctfile $< $(INCLUDE) -L. $(LIBDIR) -l{0} $(LIBS) -o {1}"
                        .format(name,name_oct))

    if rpc:
        makefile.rule("server", [], "make -C server", phony = True)
        makefile.rule("server-mpi", [], "make -C server mpi", phony = True)

    deps = [ name_o ] + other_deps
    deps_mpi = [ name_mpi_o ] + other_deps
    makefile.rule(libname_a, deps, "ar -cr lib{0}.a ".format(name) + " ".join(deps))

    makefile.rule(libname_mpi_a, deps_mpi, "ar -cr lib{0}_mpi.a ".format(name) + " ".join(deps_mpi))
    makefile.rule(name_mpi_o,
                  [ name_cpp ],
                  "$(MPICXX) -DCA_MPI $(CFLAGS) $(INCLUDE) -c {0} -o {1}"
                    .format(name_cpp, name_mpi_o))

    all = deps + [ name_mpi_o, libname_a, libname_mpi_a ]

    if project.library_octave:
        all.append(name_oct)

    clean_command = "rm -f {0}".format(" ".join(all))

    if rpc:
        clean_command += " && make -C server clean"

    makefile.rule("clean", [], clean_command, phony = True)
    makefile.write_to_file(os.path.join(directory, "makefile"))