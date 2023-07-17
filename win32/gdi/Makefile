CC := gcc
# CFLAG := 
LDFLAG := -Wl,--subsystem,windows -lgdi32 -luser32 -lkernel32 -lcomctl32 -lm -mwindows

SRCS := $(wildcard *.c)
# SRCS := main.c
EXE := $(SRCS:%.c=%.exe)

all:
	$(CC) $(LDFLAG) $(SRCS) -o $(EXE)

clean:
	rm -rf $(EXE)