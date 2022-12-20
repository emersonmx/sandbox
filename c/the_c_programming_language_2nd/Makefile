CC=gcc
CFLAGS=-g -Wall

sourcefiles = $(wildcard *.c */*.c)
objectfiles = $(patsubst %.c,%.o,$(sourcefiles))
binfiles = $(patsubst %.c,%,$(sourcefiles))

.PHONY: all clean format

all: $(binfiles)

format: $(sourcefiles)
	clang-format -i $^

clean: $(binfiles)
	rm -f $^
