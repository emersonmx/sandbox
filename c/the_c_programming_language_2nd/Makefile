CC=gcc
CFLAGS=-g -Wall

sourcefiles = $(wildcard *.c */*.c)
objectfiles = $(patsubst %.c,%.o,$(sourcefiles))
binfiles = $(patsubst %.c,%,$(sourcefiles))

.PHONY: all clean

all: $(binfiles)

clean: $(binfiles)
	rm -f $^
