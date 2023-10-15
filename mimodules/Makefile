

DESTDIR=
LIBDIR=/usr/lib
INCLUDEDIR=/usr/include

INCLUDES = -I. -I/.
CXX_FLAGS = -fpic -Wall
LD_FLAGS = -shared -lpthread -lmidriver -lmiutils

SOURCES=ModuleBase.cpp ModuleBuffer.cpp ModuleHoerterInput.cpp ModuleHoerterOutput.cpp ModulePointer.cpp ModuleManager.cpp ModuleValue.cpp ModuleMiPotentiometer.cpp
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARYOUT=libmimodule.so


.cpp.o:
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $<
$(LIBRARYOUT):$(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $(LIBRARYOUT)
clean:
	$(RM) $(LIBRARYOUT) *.o
	

install: $(LIBRARYOUT)
	mkdir -p $(DESTDIR)/$(LIBDIR)
	mkdir -p $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleBase.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleBuffer.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleHoerterInput.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModulePointer.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleManager.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleValue.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleTypes.h $(DESTDIR)/$(INCLUDEDIR) 
	cp ModuleChannel.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleInterface.h $(DESTDIR)/$(INCLUDEDIR)
	cp ModuleMiPotentiometer.h $(DESTDIR)/$(INCLUDEDIR)
	cp $(LIBRARYOUT) $(DESTDIR)/$(LIBDIR)