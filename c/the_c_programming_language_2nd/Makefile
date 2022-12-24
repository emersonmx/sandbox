CC=gcc
CFLAGS=-g -Wall

sourcefiles = $(wildcard *.c */*.c)
binfiles = $(patsubst %.c,%,$(sourcefiles))

.PHONY: all clean format

all: $(binfiles)

format: $(sourcefiles)
	clang-format -i $^

clean: $(binfiles)
	rm -f $^
