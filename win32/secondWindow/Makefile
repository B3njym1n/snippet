CC = g++
RES = resources
EXE = main
WINDRES = windres
CXXFLAGS = -I${RES}/ -Wall -D_WIN32_WINNT=0x0600
LDFLAGS = -lgdi32

all:
	$(WINDRES) $(RES)/resource.rc -o $(RES)/resource.o
	mkdir -p bin/
	$(CC) $(CXXFLAGS) src/main.cpp $(RES)/resource.o $(LDFLAGS) -o bin/$(EXE)

clean:
	rm -rf bin/$(EXE) $(RES)/resource.o