DESTDIR=
prefix=/usr
includedir=$(prefix)/include
libdir=$(prefix)/lib

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
	install -d $(DESTDIR)/${libdir}
	install -D -m 0644 $(LIBRARYOUT) $(DESTDIR)/${libdir}/$(LIBRARYOUT)
	install -d $(DESTDIR)/${includedir}
	install -d $(DESTDIR)/${includedir}/mi
	install -d $(DESTDIR)/${includedir}/mi/mimodule
	install -D -m 0644 ModuleBase.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleBase.h
	install -D -m 0644 ModuleBuffer.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleBuffer.h
	install -D -m 0644 ModuleHoerterInput.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleHoerterInput.h
	install -D -m 0644 ModulePointer.h $(DESTDIR)/${includedir}/mi/libmimodules/ModulePointer.h
	install -D -m 0644 DriverBase.h $(DESTDIR)/${includedir}/mi/libmimodules/DriverBase.h
	install -D -m 0644 ModuleManager.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleManager.h
	install -D -m 0644 ModuleValue.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleValue.h
	install -D -m 0644 ModuleTypes.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleTypes.h
	install -D -m 0644 ModuleChannel.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleChannel.h
	install -D -m 0644 ModuleInterface.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleInterface.h
	install -D -m 0644 ModuleMiPotentiometer.h $(DESTDIR)/${includedir}/mi/libmimodules/ModuleMiPotentiometer.h