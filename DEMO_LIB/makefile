BUILD_OS=none
ANTLIB_PATH = ../ANT_LIB

# OS Specification Code (either auto detected or manually specified with the OS variable on command line
# OSX will default to libusb if FRAMEWORK_TYPE is not specified.
ifeq ($(OS), osx)
    $(info OSX Specified)
    BUILD_OS = osx
else ifeq ($(OS), linux)
    $(info Linux Specified)
    BUILD_OS = linux
else 
    ifeq ($(OS),Windows_NT)
        $(info Please use the Visual Studio Project for Windows)
    else
        UNAME_S := $(shell uname -s)
        ifeq ($(UNAME_S),Darwin)
            $(info OSX Detected)
            BUILD_OS = osx
        else ifeq ($(UNAME_S),Linux)
            $(info Linux Detected)
            BUILD_OS = linux
        else
            $(info Linux Assumed)
            BUILD_OS = linux
        endif
    endif
endif

ifeq ($(BUILD_OS), linux)
    LINKER_ARGUMENTS = -pthread -L$(ANTLIB_PATH)/gccDebug -Wl,--start-group -lANT_LIB -Wl,--end-group -Wl,-rpath,./ -lrt
else ifeq ($(BUILD_OS), osx)
    ifeq ($(FRAMEWORK_TYPE), iokit)
        $(info using IOkit)
        LIBRARY_PATH = -LFoundation.framework
        FRAMEWORKS = -framework IOKit -framework Foundation
        LINKER_ARGUMENTS = -L$(ANTLIB_PATH)/gccDebug -lANT_LIB -Wl,-rpath,./ -lobjc $(FRAMEWORKS)
    else ifeq ($(FRAMEWORK_TYPE), libusb)
        $(info using libusb)
        FRAMEWORKS = -framework IOKit -framework Foundation
        LINKER_ARGUMENTS = -L$(ANTLIB_PATH)/gccDebug -lANT_LIB -Wl,-rpath,./ -lobjc $(FRAMEWORKS)
    else
        $(info using libusb)
        FRAMEWORK_TYPE = libusb
        FRAMEWORKS = -framework IOKit -framework Foundation
        LINKER_ARGUMENTS = -L$(ANTLIB_PATH)/gccDebug -lANT_LIB -Wl,-rpath,./ -lobjc $(FRAMEWORKS)
    endif
endif


INCLUDE_PATH = -I$(ANTLIB_PATH)/inc -I$(ANTLIB_PATH)/software/serial -I$(ANTLIB_PATH)/software/serial -I$(ANTLIB_PATH)/software/system -I$(ANTLIB_PATH)/software/serial/device_management -I$(ANTLIB_PATH)/software/serial -I$(ANTLIB_PATH)/software/USB -I$(ANTLIB_PATH)/software/USB/devices -I$(ANTLIB_PATH)/software/USB/device_handles -I$(ANTLIB_PATH)/libraries -I$(ANTLIB_PATH)/software/USB/iokit_driver


CPP = g++ -w $(INCLUDE_PATH)
CC = gcc -ansi $(INCLUDE_PATH)
LL = g++

VPATH = $(ANTLIB_PATH)/common:$(ANTLIB_PATH)/inc:$(ANTLIB_PATH)/software/ANTFS:$(ANTLIB_PATH)/software/system:$(ANTLIB_PATH)/software/serial:$(ANTLIB_PATH)/software/serial/device_management:$(ANTLIB_PATH)/software/USB:$(ANTLIB_PATH)/software/USB/devices:$(ANTLIB_PATH)/software/USB/device_handles:$(ANTLIB_PATH)/libraries:$(ANTLIB_PATH)/software/USB/iokit_driver

APP_OBJECTS = demo.o

all: lib demo

lib:
	cd $(ANTLIB_PATH) ; make FRAMEWORK_TYPE=$(FRAMEWORK_TYPE)

demo: $(APP_OBJECTS)
	$(LL) $(APP_OBJECTS) $(LINKER_ARGUMENTS) -o $@

demo.o: demo.cpp demo.h types.h dsi_vcp_si.hpp dsi_framer_ant.hpp dsi_thread.h
	$(CPP) -c -o $@ $<

clean:
	rm -f *.o	
	cd $(ANTLIB_PATH) ; make clean
