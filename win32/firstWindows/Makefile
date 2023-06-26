CC = gcc
RC = windres
EXE = Win32App.exe
WARNS = -Wall

BUILD_DIR := ./build

SRCS := $(wildcard *.c)

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CFLAGS = -O2 -std=c99 -D _WIN32_IE=0x0500 -D WINVER=0x0500 $(WARNS)

LDFLAGS = -s -lcomctl32 -Wl,--subsystem,windows

.PHONY: clean

all: $(BUILD_DIR)/$(EXE)

clean:
	rm -rf $(BUILD_DIR)

$(OBJS): $(SRCS)
	mkdir -p $(dir $@)
	$(CC) -c $^ -o $@

$(BUILD_DIR)/$(EXE): $(OBJS)
	$(CC) $^ -o $@

