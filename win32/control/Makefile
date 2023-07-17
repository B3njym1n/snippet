CC := gcc
LDFLAG :=  -Wl,--subsystem,windows
SRCS := main.c
EXE := $(SRCS:%.c=%.exe)

all: main

main:
	$(CC) $(SRCS) $ $(LDFLAG) -o $(EXE)

clean:
	rm $(EXE)