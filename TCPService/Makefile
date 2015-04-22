OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64
  else
    LEAP_LIBRARY := ../lib/x86/libLeap.so -Wl,-rpath,../lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := ../lib/libLeap.dylib
endif


all:TCPS TCPC

TCPS: TCPS.cpp
	$(CXX) -Wall -g -I../header TCPS.cpp -o TCPS $(LEAP_LIBRARY)
ifeq ($(OS), Darwin)
	install_name_tool -change @loader_path/libLeap.dylib ../lib/libLeap.dylib TCPS
endif

TCPC: TCPC.c
	$(CC) -Wall TCPC.c -o TCPC

.PHONY:all

clean:
	rm -rf TCPS TCPS.dSYM TCPC TCPC.dSYM
