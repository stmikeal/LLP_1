CC=gcc
INCLUDES=-I./include
CFLAGS=-O3 -Wall -Wextra $(INCLUDES)
DEBUG_CFLAGS=-DDEBUG -g3

TARGET=main
TARGET_TEST=test

SRC_DIR=src
HEADER_DIR=include
TARGET_DIR=build

SOURCES  = $(shell find ./$(SRC_DIR) -name "*.c")
HEADERS  = $(shell find ./$(HEADER_DIR) -name "*.h")

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

all: build run

run:
	./$(TARGET)

build: $(SOURCES) $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET_DIR)/$@

clean:
	rm -rf $(BUILDDIR) $(TARGET_DIR)


