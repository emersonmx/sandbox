CC=gcc
CFLAGS=-g -Wall

sourcefiles = $(wildcard *.c */*.c)
binfiles = $(patsubst %.c,%,$(sourcefiles))

.PHONY: all clean format

all: $(binfiles)

format:
	clang-format -i *.c

clean: $(binfiles)
	rm -f $^
