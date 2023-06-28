CC := gcc
# CFLAG := 
LDFLAG := -lgdi32 -luser32 -lkernel32 -lcomctl32 -lm -mwindows
EXE := draw
SRCS := $(wildcard *.c)

all:
	$(CC) $(LDFLAG) $(SRCS) -o $(EXE)

clean:
	rm -rf $(EXE).exe