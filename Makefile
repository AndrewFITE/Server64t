target =  main
sources = main.cpp communicator.cpp err_writer.cpp interface.cpp
test_sources = communicator.cpp err_writer.cpp interface.cpp tests.cpp
CC = g++
CCFlags = -Wall
LDLIBS = -lcrypto++
OPT = -Ofast
all:build
build:
	$(CC) $(CCFlags) $(OPT) $(sources) -o $(target) $(LDLIBS)

test: tests.cpp
	$(CC) $(CCFlags) $(OPT) -DMY_UNIT_TEST $(test_sources) -o test $(LDLIBS) -lUnitTest++
dbg:
	$(CC) -g $(sources) -o $(target)DBG
