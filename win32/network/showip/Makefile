CC := gcc
SRCS := $(wildcard *.c)
EXE := $(SRCS:%.c=%.exe)
LDFLAG := -lws2_32

showip:
	$(CC) -Wall $(SRCS)  -Wl,--subsystem,windows -o $(EXE) $(LDFLAG)

clean:
	rm -rf $(EXE)