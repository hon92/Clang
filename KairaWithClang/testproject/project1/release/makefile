# This file is autogenerated.
# Do not edit directly this file.

KAIRA_PATH=/home/honza/Plocha/kaira-git
CXX=/usr/bin/g++
CFLAGS=-O2
INCLUDE=-I${KAIRA_PATH}/libs/cailie -I.. 
LIBDIR=-L${KAIRA_PATH}/build/libs/cailie 
LIBS=  -lcailie -lpthread -lrt 
MPICXX=/usr/bin/mpic++
MPILIBS=  -lcailiempi -lpthread -lrt 
.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@
.cc.o:
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@
.c.o:
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@
.PHONY: all
all: project1
project1: project1.o
	$(CXX) project1.o -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(LIBS) 
project1.o: project1.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c project1.cpp -o project1.o
.PHONY: clean
clean:
	rm -f project1 project1.o project1_mpi project1_mpi.o
.PHONY: mpi
mpi: project1_mpi
project1_mpi: project1_mpi.o
	$(MPICXX) -D CA_MPI project1_mpi.o -o $@ $(CFLAGS) $(INCLUDE) $(LIBDIR) $(MPILIBS)
project1_mpi.o: project1.cpp
	$(MPICXX) -DCA_MPI $(CFLAGS) $(INCLUDE) -c project1.cpp -o project1_mpi.o
