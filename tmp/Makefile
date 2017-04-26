# Target     
PROGRAM = fann.node

LIBS = "../lib/"  
    
NODE_LIB = node.lib 
FANN_LIB = fannfloat.lib  ## fannfixed.lib fanndouble.lib    
    
node = "../node/"    
inc = "../inc/"    
src = "../src/"      
INCLUDEDIRS =  /I $(inc) /I $(node) /I $(LIBS)
   
# Flags    
CPPOPT = $(INCLUDEDIRS) /w /EHsc /D_CRT_SECURE_NO_DEPRECATE    
    
# Compiler     
cc = cl     
CFLAGS =     
     
LFLAGS = /LIBPATH:$(LIBS)     
     
# list of source files     
CPPSOURCES =  addon.cc  ynodefann.cc \
               ynodefanntraindata.cc     
    
# expands to list of object files            
CPPOBJECTS = $(CPPSOURCES:.cc=.obj)     
      
all: $(PROGRAM)    
    
$(PROGRAM): $(CPPOBJECTS)    
    link.exe /out:../build/Release/$(PROGRAM) /DLL  $(CPPOBJECTS) $(LFLAGS) $(NODE_LIB) $(FANN_LIB)    
        
addon.obj:     
    $(cc) $(CPPOPT) /c ../src/addon.cc         
  
ynodefann.obj:     
    $(cc) $(CPPOPT) /c ../src/ynodefann.cc         
      
ynodefanntraindata.obj:     
    $(cc) $(CPPOPT) /c ../src/ynodefanntraindata.cc         
            
clean:      
    del $(CPPOBJECTS) $(PROGRAM)          