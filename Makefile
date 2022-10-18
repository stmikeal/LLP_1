CC=gcc
CFLAGS=--std=c17 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG

BUILDDIR=build
SRCDIR=src
TARGETDIR=.

SOURCES=$(shell find ./$(SRCDIR) -name "*.c")
EXECUTABLE=main

.PHONY: all
all: build run clean

run:
	./$(EXECUTABLE)

build: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) -o $@

clean:
	rm -rf $(BUILDDIR) $(EXECUTABLE)
