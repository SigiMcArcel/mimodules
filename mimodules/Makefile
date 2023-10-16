DESTDIR=
prefix=/usr
includedir=$(prefix)/include
libdir=$(prefix)/lib

INCLUDES = -I. -I/.
CXX_FLAGS = -fpic -Wall
LD_FLAGS = -shared -lpthread -lmidriver -lmiutils

SOURCES=ModuleBase.cpp ModuleBuffer.cpp ModuleHoerterInput.cpp ModuleHoerterOutput.cpp ModulePointer.cpp ModuleManager.cpp ModuleValue.cpp ModuleMiPotentiometer.cpp
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARYOUT=libmimodules.so


.cpp.o:
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $<
$(LIBRARYOUT):$(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $(LIBRARYOUT)
clean:
	$(RM) $(LIBRARYOUT) *.o
	

install: $(LIBRARYOUT)
	install -d $(DESTDIR)/${libdir}
	install -D -m 0644 $(LIBRARYOUT) $(DESTDIR)/${libdir}/$(LIBRARYOUT)
	install -d $(DESTDIR)/${includedir}
	install -d $(DESTDIR)/${includedir}/mi
	install -d $(DESTDIR)/${includedir}/mi/mimodules
	install -D -m 0644 ModuleBase.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleBase.h
	install -D -m 0644 ModuleBuffer.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleBuffer.h
	install -D -m 0644 ModuleHoerterInput.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleHoerterInput.h
	install -D -m 0644 ModulePointer.h $(DESTDIR)/${includedir}/mi/mimodules/ModulePointer.h
	install -D -m 0644 ModuleHoerterOutput.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleHoerterOutput.h
	install -D -m 0644 ModuleManager.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleManager.h
	install -D -m 0644 ModuleValue.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleValue.h
	install -D -m 0644 ModuleTypes.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleTypes.h
	install -D -m 0644 ModuleChannel.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleChannel.h
	install -D -m 0644 ModuleInterface.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleInterface.h
	install -D -m 0644 ModuleMiPotentiometer.h $(DESTDIR)/${includedir}/mi/mimodules/ModuleMiPotentiometer.h