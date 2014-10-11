import gtksourceview2 as gtksource
import gtk
# from tools.Buffer import Buffer
# from tools.CompletionProvider import CompletionProvider
# from tools.ClangParser import ClangParser
# from tools.Settings import Settings
# from tools.Completion import Completion



class View(gtksource.View):
        
    def __init__(self,buffer = None):
        gtksource.View.__init__(self,buffer)
        self.buffer = buffer              
        self.codeCompletion = None
        self.set_property("highlight-current-line",True)
        self.set_wrap_mode(gtk.WRAP_CHAR)
  
        