import gtksourceview2 as gtksource
import gtk
import paths
import os
import time
import cProfile
import gobject
import clang.cindex as clanglib
from ClangParser import ClangParser
from CompletionProvider import CompletionProvider
from ProposalItem import ProposalItem



class ResultKindFilter():
    def __init__(self,defaultmap):
        self.defaultmap = defaultmap
        self.filteredmap = dict(defaultmap)
    def filterByKindId(self,id):
        pass
            
    def filterByName(self,names):
        for k in self.filteredmap.keys():
            if self.filteredmap[k][1] not in names:
                del self.filteredmap[k]
    def resetFilter(self):
        self.filteredmap = dict(self.defaultmap)
    def getMap(self):
        return self.filteredmap
resultKindMap = dict()


def initKindMap(resultKindMap):
    maps = {
    0 : ([9,6,10],-100,"var"),
    1 : ([2,3,4,20,31,32],-85,"class"),
    2 : ([8,26,27,28,29,30],-90,"func"),
    3 : ([21],-92,"func"),
    4 : ([22,33],-80,"namespace"),
    5 : ([5],-78,"enum"),
    6 : ([7],-75,"enumerator"),
    #7 : ([500,501,502,503],-70,"macro"),
    8 : ([72],-40,"snippet")
    }
    for v in maps.values():
        iconname = v[2]
        priority = v[1]
        for value in v[0]:
            resultKindMap[value] = (priority,iconname)
    
initKindMap(resultKindMap) 
    
class KeyPressedMap():
    
    def __init__(self):
        self.keys = []
    def count(self):
        return len(self.keys)
    def keyPressed(self,key):
        if len(self.keys) > 0:
            if self.keys[-1] == key.keyval:
                self.removeAll()
                
        self.keys.append(key.keyval)
        
    def keyReleased(self,key):
        for i in range(len(self.keys)):
            if self.keys[i] == key.keyval:
                del self.keys[i]
                return
    def removeAll(self):
        self.keys = []
        return
        for i in range(len(self.keys)):
            del self.keys[i]
            
    
class PlaceHolderObject():
    items = []
    
    def __init__(self,iter,proposal,buffer,view):
        
        self.enditer = iter.copy()
        self.proposal = proposal
        self.buffer = buffer
        self.place = proposal.getPlaceholders()
        self.maxnum = len(self.place)
        self.current = 0
        self.text = proposal.get_property("text")       
        self.startiter = iter.copy()
        self.startiter.set_offset(iter.get_offset() - len(self.text))
        self.view = view
        self.marks = []
        self.labels = []
        
        self.eb = gtk.EventBox()      
        self.lab = gtk.Label("")
        
        for place in self.place:
            temp = place.replace("&","&amp;")
            temp = temp.replace(">","&gt;")
            temp = temp.replace("<","&lt;")
            self.labels.append(temp)
       
        
        self._setMarks()
        
        self.eb.add(self.lab)
        self.eb.modify_bg(gtk.STATE_NORMAL,gtk.gdk.Color("black"))
        
        
        self.view.add_child_in_window(self.eb,gtk.TEXT_WINDOW_TEXT,0,0)
        self.selectIndex(0)
        self.view.show_all()
        PlaceHolderObject.items.append(self.eb)
  

    def _setMarks(self):
        tempiter = self.startiter.copy()
        lastmarkchar = ""
        for i in range(len(self.place)):
            startmark = None
            endmark = None
            
            placeholder = self.text.find(self.place[i],0)
            iter = self.buffer.get_iter_at_offset(tempiter.get_offset() + placeholder-1)
            
            if i ==0 or lastmarkchar != ",":
                startmark = self.buffer.create_mark(None,iter)
                
            
            iter.set_offset(iter.get_offset() + len(self.place[i])+1)
            lastmarkchar = iter.get_char()
            
            endmark = self.buffer.create_mark(None,iter)
            
            
            if not startmark:
                lastendmark = self.marks[len(self.marks)-1][1]
                startmark = lastendmark
                
            self.marks.append((startmark,endmark))
        
         
    def hide(self):
        
        for mark in self.marks:
            self.buffer.delete_mark(mark[0])
            self.buffer.delete_mark(mark[1])
        
        
        childrens = PlaceHolderObject.items
        for child in childrens:
            self.view.remove(child)
            PlaceHolderObject.items.remove(child)
        
    def selectIndex(self,index):
        if index < 0 or index > self.maxnum:
            return
        
        startmark,endmark = self.marks[index]
        startiter = self.buffer.get_iter_at_mark(startmark)
        enditer = self.buffer.get_iter_at_mark(endmark)
        #print "start: ","["+ startiter.get_char()+"]", "    " , "end: ","["+ enditer.get_char()+"]", " ------- " ,"["+self.buffer.get_text(startiter,enditer) + "]"
        startiter.set_offset(startiter.get_offset() + 1)
        self.buffer.select_range(startiter,enditer) 
        rectangle = self.view.get_iter_location(startiter)
        rectangle.x,rectangle.y = self.view.buffer_to_window_coords(gtk.TEXT_WINDOW_TEXT,rectangle.x,rectangle.y)      
        info = self.labels[index]
   
        text = '<span color="white">' + info +  '</span>'
        self.lab.set_markup(text)
        self.view.move_child(self.eb,rectangle.x,rectangle.y-20)    
        
    def next(self):
        if self.current +1 < self.maxnum:
            self.current += 1
        else:
            self.current = 0
        self.selectIndex(self.current)
        
class InfoBox(gtk.EventBox):
    def __init__(self,completion):
        gtk.EventBox.__init__(self)
        self.completion = completion
        self.label = gtk.Label("")
        self.add(self.label)
        self.completion.view.add_child_in_window(self,gtk.TEXT_WINDOW_TEXT,0,0)
        self.completion.view.connect("motion_notify_event",self.mouseMove)
    def changeText(self,text):
        self.label.set_text(text)
    def mouseMove(self,view,e):
        x,y = self.completion.view.window_to_buffer_coords(gtk.TEXT_WINDOW_TEXT,int(e.x),int(e.y))
        self.completion.view.move_child(self,int(e.x+50),int(e.y))
        iter = self.completion.view.get_iter_at_location(int(x),int(y))
        line = iter.get_line()+1
        col = iter.get_line_offset()
        cursor = self.completion.cursorUnderMouse(line,col)
        
        if self.completion.clang.type == "head":
            line-= self.completion.clang.lineoffset
                
        if self.completion.codeErrorList.has_key(line-1):
                errorcodeinfo = self.completion.codeErrorList[line-1]
                if col >= errorcodeinfo[0] and col <= errorcodeinfo[1]:
                    self.changeText("Error: " + errorcodeinfo[2])
                    self.show_all()
                    return
        if cursor:
            info = self._infoFromCursor(cursor)
            self.changeText(info)
        
        
    def _infoFromCursor(self,cursor):
        type = cursor.type.kind.spelling
        resulttype = cursor.result_type.kind.spelling
        name = cursor.displayname
        definition = cursor.kind.name
                
        if cursor.type.kind.name == "INVALID":
            self.hide_all()
        else:
            self.show_all()
        
        infotext = ""
        
        if name:
            infotext += "Name: " + name + "\n"
        if type and type != "Unexposed":
            infotext += "Type: " + type + "\n"
        if resulttype and resulttype != "Invalid" and resulttype != "Unexposed":
            infotext += "Result Type: " + resulttype + "\n"
        if definition:
            infotext += "Definition: " + definition
            
        return infotext



     
def loadProposalsIcons():        

    theme = gtk.IconTheme()
    path = os.path.join(paths.ICONS_DIR, "ProposalsIcons")
    theme.set_search_path([path])
    data = theme.list_icons()
    icons = {}
        
    for icon in data:
        icons[icon] = theme.load_icon(icon,16,0)
    return icons

icons = loadProposalsIcons()
       

class Completion(gobject.GObject):
    prefixchars = [";"," ","(",".",">",":","<","[","]",")","#","-","{","}","=","\n"]      
               
    def __init__(self,codeeditor,project):
        gobject.GObject.__init__(self) 
        self.codeeditor = codeeditor
        self.view = codeeditor.view
        self.resultKindFilter = ResultKindFilter(resultKindMap)
        self.completion = self.view.get_completion()
        
        self.completion.set_property("remember-info-visibility",True)
        self.completion.set_property("auto-complete-delay",0)
        self.completion.set_property("accelerators",0)
        self.completion.set_property("select-on-show",True)
        
        self.project = project
        self.clang = ClangParser(self)
        self.provider = CompletionProvider(self)
        self.completion.add_provider(self.provider)
        self.icons = icons            
        self.infoBox = None  
                         
        self.view.connect("key_press_event",self._keyPressed)
        self.view.connect("key_release_event",self._keyReleased)
        self.view.connect("button_press_event",self.mouseClick)
        self.completion.connect("show",self.windowShowed)
        self.completion.connect("hide",self.windowHidden)
        self.view.buffer.connect("changed",self.textChanged)
        self.view.buffer.connect_after("insert-text",self.textInserted)
        
        
        
        self.kindmap = self.resultKindFilter.getMap()
        self.tu = None
        self.prefix = ""
        self.keymap = KeyPressedMap()
        self.windowShowed = False
        self.results = []
        self.lastCC = (1,1)
        self.codeChanged = True
        self.insertedItem = False
        self.lastSelectedItem = None
        self.placeHolderObject = None
        self.view.show_all()
        self.codeErrorList = {}
        
    def setInfoBox(self,enable):
        if enable is True:
            self.infoBox = InfoBox(self)
        else:
            self.infoBox = None
    def setRefactoring(self,enable):
        if enable is True:
            def populatePopup(view,menu):
                item = gtk.MenuItem("Refactoring")
                refactoringMenu = gtk.Menu()
                renameMenu = gtk.MenuItem("Rename")
                refactoringMenu.add(renameMenu)
                item.set_submenu(refactoringMenu)
                                
                renameMenu.connect("activate",self.refactorCode)
                menu.append(item)
                menu.show_all()
                
            self.view.connect("populate-popup",populatePopup)
        #TODO: if setRefactoring is enabled then cant be disabled because signal is not disconnected
    def windowHidden(self,w):
        if self.windowShowed:
            self.windowShowed = False
    def windowShowed(self,w):
        self.windowShowed = True
    
    
        
    def refactorCode(self,widget):
        buffer = self.view.buffer
        if buffer.get_has_selection():
            s= buffer.get_selection_bounds()[0]
            line = s.get_line() +1
            col = s.get_line_offset()+1
            
            cursor = self.cursorUnderMouse(line, col)
            referenced = None
            
            if cursor:  
                referenced = cursor.referenced
            
            if not referenced or not(cursor.kind.is_expression() or cursor.kind.is_declaration()):
                return
                        
            
            oldtext = cursor.spelling
            if not oldtext:
                oldtext = cursor.displayname
                     
            dialog = gtk.Dialog("Insert new name",None,gtk.DIALOG_MODAL,(gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                    gtk.STOCK_OK, gtk.RESPONSE_ACCEPT))
            dialog.set_position(gtk.WIN_POS_CENTER_ON_PARENT)
            dialog.set_size_request(300,100)
            
            entry = gtk.Entry()
            entry.set_text(oldtext)
        
            dialog.vbox.pack_start(entry)
            entry.show()
            response = dialog.run()
            
            newtext = ""
            if response == gtk.RESPONSE_ACCEPT:
                newtext = entry.get_text()
                dialog.destroy()
            else:
                dialog.destroy()
                return
            
            if not newtext:
                return
                 
            loc = referenced.location
            if self.clang.type == "header" or (loc.line < self.clang.lineoffset and (self.clang.type == "node")):
                #Parse all project
                self.renameCodeInNodes(referenced,oldtext,newtext)
                print "Parse all"
            else:
                self.renameCodeInNode(self.codeeditor,referenced,oldtext, newtext)
                print "Parse node"
                #parse only node
#             
    def renameCodeInNode(self,node,referencedCursor,oldname,newname):
        
        places = []
        
        self.findCursorUses(self.tu, self.tu.cursor, referencedCursor, places)
        
        tempbuffer = gtk.TextBuffer()
        tempbuffer.set_text(node.buffer.getAllText())  
                
        print places
        s,e = node.get_section_iters("")        
        
        sline = s.get_line()
        eline = e.get_line()
         
        length = len(oldname)
        marks = []
        
        for location in places:
            line = location.line - 1 - self.clang.lineoffset
            col = location.column-1
            iter = tempbuffer.get_iter_at_line(line)
            iter.set_line_offset(col)
            marks.append(tempbuffer.create_mark(None,iter))
            
        for mark in marks:
            startiter = tempbuffer.get_iter_at_mark(mark)
            enditer = startiter.copy()
            enditer.set_line_offset(enditer.get_line_offset() + length)
            tempbuffer.delete(startiter,enditer)
            tempbuffer.insert(startiter,newname)
            tempbuffer.delete_mark(mark)
            
        #print tempbuffer.get_text(tempbuffer.get_start_iter(),tempbuffer.get_end_iter())
        newcode = tempbuffer.get_text(tempbuffer.get_iter_at_line(sline),tempbuffer.get_iter_at_line(eline))
        self.codeeditor.set_text(newcode)
        
    def renameCodeInNodes(self,referencedCursor,oldname,newname):
        headcode = self.project.get_head_comment() + self.clang.cailielib + self.project.get_head_code()
        lineoffset = headcode.count("\n")  
        net = self.project.nets[0]
        gen = self.project.get_generator()
        temptu = clanglib.TranslationUnit.from_source("c.cpp", None, [("c.cpp",headcode)])
        
        location = referencedCursor.location
        tempbuffer = gtk.TextBuffer()
        places = net.places()
        transitions = net.transitions()
        length = len(oldname)
        
        items = []
        items.append(headcode)
        nodeinfo = []
        indexline = lineoffset
        
        for place in places:
            placecode = "".join(["\n",gen.get_place_user_fn_header(place.get_id(),True),"{\n",place.code,"}\n"])
            endlines = placecode.count("\n")
            items.append(placecode)
            nodeinfo.append((indexline+1+2,indexline+endlines-1,place))
            indexline+=endlines
        
        for transition in transitions:
            headcode = gen.get_transition_user_fn_header(transition.get_id(),True)
            transitioncode = "".join([headcode,"{\n",transition.code,"}\n"])
            endlines = transitioncode.count("\n")
            items.append(transitioncode)
            nodeinfo.append((indexline + headcode.count("\n")+1,indexline+endlines+1-2,transition))
            indexline+=endlines
        
        allcode = "".join(items)
        tempbuffer.set_text(allcode)
            
        temptu.reparse([("c.cpp",allcode)])
        ref = clanglib.Cursor.from_location(temptu, location)
        where = []
        self.findCursorUses(temptu, temptu.cursor, ref, where)
                    
        for loc in where:
            
            line = loc.line - self.clang.libCount
            col = loc.column-1           
                 
            iter = tempbuffer.get_iter_at_line(line)
            iter.set_line_offset(col)
            mark = tempbuffer.create_mark(None,iter)
         
            startiter = tempbuffer.get_iter_at_mark(mark)
            enditer = startiter.copy()
            enditer.set_line_offset(enditer.get_line_offset() + length)
            tempbuffer.delete(startiter,enditer)
            tempbuffer.insert(startiter,newname)
            tempbuffer.delete_mark(mark)
        
        for info in nodeinfo:
            startline = info[0]
            endline = info[1]
            place = info[2]
            
            startiterline = tempbuffer.get_iter_at_line(startline)
            enditerline = tempbuffer.get_iter_at_line(endline)
            place.set_code(tempbuffer.get_text(startiterline,enditerline))
            
        
        startiterhead = tempbuffer.get_iter_at_line(5 + self.clang.libCount)
        enditerhead = tempbuffer.get_iter_at_line(lineoffset+1)
        self.project.set_head_code(tempbuffer.get_text(startiterhead,enditerhead))
        
        window = self.view.parent.parent.parent.parent.parent
        
        def reloadTab(tab):
            from codeedit import CodeEditor
            from mainwindow import Tab
            if(issubclass(tab.widget.__class__, CodeEditor)):
                
                if(isinstance(tab.key,str)):
                    tab.widget.set_text(self.project.get_head_code())
                else: 
                    newcode = tab.key.get_code()
                    tab.widget.set_text(newcode)
            
        
        
        window.foreach_tab(reloadTab)
        
        
    def findCursorUses(self,tu,rootcursor,referencedCursor,places):
        currentfile = tu.spelling
        for c in rootcursor.get_children():
            if not c.location.file:
                continue
            if c.location.file.name == currentfile:
                #print c.type.get_result().kind.spelling,c.spelling,c.displayname,c.kind.name
                ref = c.referenced
                if ref and ref == referencedCursor and not c.kind.is_unexposed():
                    #print c.type.get_result().kind.spelling,c.spelling,c.displayname,c.kind.name
                    kind = c.kind
                    #if kind.is_expression():# or kind.is_declaration() or kind.is_reference():
                    if kind.value != 103:
                        places.append(c.location)
                self.findCursorUses(tu,c, referencedCursor, places)
                
    def textInserted(self,buffer,iter,text,length):
        
        if self.insertedItem:
            proposal = self.lastSelectedItem
            placeholders = proposal.getPlaceholders()
            if placeholders:
                if self.placeHolderObject is None:
                    self.placeHolderObject = PlaceHolderObject(iter,proposal,buffer,self.view)
                    self.insertedItem = False
                else:
                    self.placeHolderObject.hide()
                    self.placeHolderObject = PlaceHolderObject(iter,proposal,buffer,self.view)
                    self.insertedItem = False
                                
        if text == "." and not self.windowShowed:
            self.view.emit("show-completion")
        elif text == ">" and not self.windowShowed:  
            pos = buffer.get_property("cursor-position")
            iter = buffer.get_iter_at_offset(pos-2)
            char = iter.get_char()
            if char == "-":
                self.view.emit("show-completion")
                 
        elif text == ":" and not self.windowShowed:
            pos = buffer.get_property("cursor-position")
            iter = buffer.get_iter_at_offset(pos-2)
            char = iter.get_char()
            if char == ":":
                self.view.emit("show-completion")
                
        elif text == "(":
            self.view.buffer.insert_at_cursor(")")
            pos = self.view.buffer.get_property("cursor-position")
            iter = self.view.buffer.get_iter_at_offset(pos)
            iter.set_offset(iter.get_offset() -1)
            self.view.buffer.place_cursor(iter)
        elif text == "{":
            self.view.buffer.insert_at_cursor("}")
            pos = self.view.buffer.get_property("cursor-position")
            iter = self.view.buffer.get_iter_at_offset(pos)
            iter.set_offset(iter.get_offset() -1)
            self.view.buffer.place_cursor(iter)
        
            
    
    def textChanged(self,buffer):
        if self.windowShowed:
            return
        else:
            self.codeChanged = True
            self.parseSourceCode()
    
    def mouseClick(self,w,e):
        x,y = self.view.window_to_buffer_coords(gtk.TEXT_WINDOW_TEXT,int(e.x),int(e.y))
        if gtk.keysyms.Control_L in self.keymap.keys and e.button == 1:
            iter = self.view.get_iter_at_location(int(x),int(y))
            
            cursor = self.cursorUnderMouse(iter.get_line()+1, iter.get_line_offset())
            
            if cursor: 
                referenced = cursor.referenced
                
                if referenced:    
                    location = referenced.location
                    
                    file = os.path.normpath(location.file.name)
                    if file == self.clang.file:
                        self.codeeditor.jump_to_position(("",location.line,0))
                        print "Jump to line:",location.line
                        return
                    
                    from mainwindow import Tab
                    from codeedit import CodeFileEditor
                    
                    codeedit = CodeFileEditor(self.project.get_syntax_highlight_key(),file)
                    codeedit.jump_to_position(("",referenced.location.line,0))
                    window = self.view.parent.parent.parent.parent.parent
                    tabname = os.path.basename(file)
                    tab = Tab(tabname, codeedit)
                    window.add_tab(tab,True)         
                    print "move to: ",referenced.location    
                    return True
      
    def _keyReleased(self,w,key):
        self.keymap.keyReleased(key)
    def _keyPressed(self,w,key):
        self.keymap.keyPressed(key)
        self.setprefix(key)
                
        if self.placeHolderObject:
            if key.keyval in [gtk.keysyms.Escape,gtk.keysyms.semicolon]:
                self.placeHolderObject.hide()
                self.placeHolderObject = None
            if key.keyval == gtk.keysyms.Tab:
                self.placeHolderObject.next()
                return True
             
    def setprefix(self,key):
        buffer = self.view.buffer
        pos = buffer.getCursorPosition()
        iter = buffer.get_iter_at_offset(pos)
        
        tmp = iter.copy()
        start = buffer.get_iter_at_line(iter.get_line()-1)
        text = buffer.get_text(start,tmp)
        text+= key.string
        
        if key.keyval == gtk.keysyms.BackSpace:
            text = text[:-1]
                                
        char = ""
        pre = ""
        while len(text) > 0:
            if len(text) > 0:
                char = text[-1]
                if(char in Completion.prefixchars or len(text) == 0):
                    break
                else:
                    if char != "\r" and char != "\n" and char != "" and char != "\t":
                        pre+=char
                    text = text[:-1]
            
        pre = pre[::-1]
        if pre.isdigit():
            pre = ""
        self.prefix = pre
        if self.prefix != "":
            pass#print "PREFIX:",pre
                
    def itemSelected(self,iter,proposal):
        if self.view.buffer.get_has_selection():
            start,end = self.view.buffer.get_selection_bounds()
            self.view.buffer.delete(start,end)
        self.lastSelectedItem = proposal
        self.insertedItem = True
                
    def cursorUnderMouse(self,line,col):
        if self.tu:
            
            file = clanglib.File.from_name(self.tu,self.clang.file)
            location =  clanglib.SourceLocation.from_position(self.tu, file, line + self.clang.lineoffset, col)
            cursor = clanglib.Cursor.from_location(self.tu, location)          
            return cursor
        else:
            return None
            
    def isObjectPointer(self,cursor):
        bitype = cursor.type.kind.spelling 
        if bitype == "Pointer":
            pp = cursor.type.get_pointee()
                
            while pp.kind.spelling == "Pointer":
                pp = pp.get_pointee() 
                
            pp = pp.kind.spelling
                    
            if pp == "Record":
                pointertype =  cursor.type.get_pointee()
                    
                while pointertype.kind.spelling == "Pointer":
                    pointertype = pointertype.get_pointee()
                        
                pointertype = pointertype.get_declaration().spelling
                    
                #print "pointer type obj: " + str(pointertype)
                return True
            else:
                #print "pointer type build-in: " + pp
                return False
        else:
            return False
    def isObject(self,cursor):        
        bitype = cursor.type.kind.spelling         
        if bitype == "Record":
            type =  cursor.type.get_declaration().spelling
            #print "type obj: " + type   
            return True
        else:
            return False     
        
                        
    def parseSourceCode(self):
        if not self.windowShowed:
            
            try:
                if self.tu is None:
                    self.tu = self.clang.parse()
                    self.clang.reparse()
                else:
                    t1 = time.time()
                    self.clang.reparse()
                    t2 = time.time()
                    print "Parse time: " + str(t2-t1)    
                
                    
                    self.view.buffer.remove_tag_by_name("error",self.view.buffer.get_start_iter(),self.view.buffer.get_end_iter())
                    self.codeErrorList.clear()
                    
                    for d in self.tu.diagnostics:
                        if d.severity == 3:
                            location = d.location
                            
                            info = d.spelling
                            line = location.line-1 - self.clang.lineoffset         
                            iter = self.view.buffer.get_iter_at_line(line)
                            if iter.get_chars_in_line() < location.column:
                                continue     
                            #print location              
                            starthighlightcol = location.column-1
                            endhighlightcol = None
                            fixhit = ""
                            #hasrange = False
                            
                            
                            for range in d.ranges:
                                s = range.start.column
                                e = range.end.column
                                starthighlightcol = s-1
                                endhighlightcol = e
                                #hasrange = True
                                #print "Range: " , s,"-",e
                            for fix in d.fixits:
                                s = fix.range.start.column
                                e = fix.range.end.column
                                val = fix.value
                                fixhit = val
                                starthighlightcol = s-2
                                endhighlightcol = e-1
                                #print "Fix: ",val," ",s,"-",e
                        
                            #print "Parse error:",d
                            if fixhit:
                                info += "\nFix hit: \" " + fixhit + " \""
                                
                            startiter = self.view.buffer.get_iter_at_line(line)
                            if starthighlightcol <= startiter.get_chars_in_line():                            
                                startiter.set_line_offset(starthighlightcol)
                            
                            enditer = startiter.copy()
                            
                            if not endhighlightcol:
                                enditer.forward_visible_word_ends(1)
                            else:
                                if endhighlightcol >= starthighlightcol and endhighlightcol <= enditer.get_chars_in_line():
                                    enditer.set_line_offset(endhighlightcol)
                                    
                            endhighlightcol = enditer.get_line_offset()         
                            #print "Highlight:",line+1,"c:",starthighlightcol,"-",endhighlightcol
                            self.view.buffer.apply_tag_by_name("error",startiter,enditer)
                                                        
                            self.codeErrorList[line] = (starthighlightcol,endhighlightcol,info)
                            
                        if d.severity > 2 and d.location.file == self.tu.spelling:
                            pass#print d  
                    
            except Exception,e:
                print e
                
                
    def getProposals(self,context):
        
        iter = context.get_iter()
        results = [] 
        line,col = (iter.get_line() +1, iter.get_line_offset() +1)
        col -= len(self.prefix)
        resultsToShow = None
                                
        if not self.windowShowed and (self.codeChanged or ((self.lastCC[0] != iter.get_line() or self.lastCC[1] != iter.get_line_offset() - len(self.prefix)))):
            fi = time.time()
            results = self.clang.codeComplete(line,col)
            fs = time.time()
            
            if results and len(results.results) > 0: 
                print "Clang new results len: " + str(len(results.results)),"Time of clang completion: " + str(fs-fi) 
                #cProfile.runctx("self.formatResults(results)", globals(), locals(),sort = 1)  
                for i in range(len(results.diagnostics)):
                    diag = results.diagnostics[i]
                    
                    if diag.severity > 2:
                        print "Completion error:",diag
                        loc = diag.location
                        if loc.line - self.clang.lineoffset == line:
                            print "No need to show proposals"
                            context.add_proposals(self.provider,[],True)
                            return
                
                self.results = self.formatResults(results)
                
            else:
                self.results = []   
                
            self.lastCC = (iter.get_line(),iter.get_line_offset())
            self.codeChanged = False    
            resultsToShow = self.results
                               
        else:
            temp = list(self.results)          
            filtered = []
            for i in xrange(len(temp)):
                t = temp[i]
                label = t.get_label()
                if label.startswith(self.prefix):
                    filtered.append(t)
            resultsToShow = filtered                             
            print "Filtered Proposals"
                
        context.add_proposals(self.provider,resultsToShow,True)
        print "LEN OF PROP",str(len(self.results))
    def formatResults(self,results):   
        proposals = []
        
        for result in results.results:
            resultType = None
            resultKind = result.cursorKind
            priority = 0
            iconname = ""
            info = ""
            typedtext = ""
            labeltext = ""
            placeholder = None
            #briefcomment = result.string.briefComment
            avail = result.string.availability
            
                                     
            if avail.name != "Available":
                continue
            if self.kindmap.has_key(resultKind):            
                priority,iconname = self.kindmap[resultKind]
            else:
                continue
                #priority = -10
                #iconname = "var"
                #print result.kind,result.string
                #continue            
            """
            if resultKind in [9,6,10]:#"VAR_DECL":     
                priority = -100
                iconname = "var"
            elif resultKind in [8,26,27,28,29,30]:#"FUNCTION_DECL":
                priority = -90
                iconname = "func"
            elif resultKind in [2,3,4,20,31,32]:#"CLASS_DECL" or resultKind == "STRUCT_DECL":
                priority = -85
                iconname = "class"
            elif resultKind == 21:#"CXX_METHOD":
                priority = -92 
                iconname = "func"
            elif resultKind in [22,33]:
                priority = -80
                iconname = "namespace"
            elif resultKind == 5:
                priority = -78
                iconname = "enum"
            elif resultKind == 7:
                priority = -75
                iconname = "enumerator"
            elif resultKind in [500,501,502,503]:
                priority = -70
                iconname = "macro"
                #continue
            elif resultKind == 72:
                iconname = "snippet";
                priority = -40 
            else:
                priority = -10
                iconname = "var"
            """    
            #print result.kind,priority,result.string
            chunkslist = [] 
                              
            for chunk in result.string:
                
                if chunk.isKindInformative():
                    continue
                if chunk.isKindResultType():
                    resultType = chunk
                    continue
               
                chunkinfo = chunk.spelling
                chunkslist.append(chunkinfo)
                
                if chunk.isKindTypedText():
                    typedtext = labeltext = chunkslist[-1]
                else:
                    typedtext = ''.join(chunkslist)
                if chunk.isKindPlaceHolder():
                    if not placeholder:
                        placeholder = []
                    placeholder.append(chunkslist[-1]) 
              
            info = ''.join(chunkslist)
           
            if self.prefix and not typedtext.startswith(self.prefix):
                continue 
            
            if priority == -40 and not placeholder:
                iconname = "keyword"
                priority = -35                      
                
            icon = self.icons[iconname]
            
            if resultType:
                labeltext = ''.join((labeltext,"  ->  ",resultType.spelling))
            
                        
            item = ProposalItem(labeltext,typedtext,icon)
            #item.setInfoText(info)
            
            #bc = briefcomment.spelling
            # if bc:
            #    info += "\nInformation: " + bc
            if placeholder:
                item.setPlaceholders(placeholder)
            item.set_property("info",info)
                        
            proposals.append((item,priority))
            
        self.sortProposals(proposals)                         
        prop = [ r[0] for r in proposals ]
        return prop
        
          
    def sortProposals(self,proposals):
        def compare(a, b):
            if a[1] < b[1]:
                return -1
            if a[1] > b[1]:
                return 1
            return cmp(a[0].get_label(), b[0].get_label())
                
        proposals.sort(compare) 
    def setFilterMask(self,mask):
        
        if type(mask) is type([]):
            self.resultKindFilter.filterByName(mask)
            self.kindmap = self.resultKindFilter.getMap()
        
     

