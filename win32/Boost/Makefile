CC := g++
CXXFLAG := -Wall -Wextra
INCLUDE := -I'c:/boost_1_79_0/'
SRCS := $(wildcard *.cpp)
EXE := $(SRCS:%.cpp=%.exe)

all: test

test:
	$(CC) $(CXXFLAG) $(SRCS) -o $(EXE) $(INCLUDE)

clean:
	rm $(EXE)