CC=gcc 
CFLAGS=--std=c17 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG -g3

BUILDDIR=build
SRCDIR=src
TARGETDIR=.

SOURCES=C:\Data\LLP_1\src\main.c C:\Data\LLP_1\src\commands\add_command.c C:\Data\LLP_1\src\commands\find_command.c C:\Data\LLP_1\src\commands\remove_command.c C:\Data\LLP_1\src\commands\update_command.c C:\Data\LLP_1\src\filetools\basic_file_manager.c C:\Data\LLP_1\src\filetools\big_data_tools.c C:\Data\LLP_1\src\generator\empty_generator.c C:\Data\LLP_1\src\interface\basic_crud.c C:\Data\LLP_1\src\interface\crud_interface.c C:\Data\LLP_1\src\ui\console_tools.c C:\Data\LLP_1\src\ui\interactive.c
EXECUTABLE=main

.PHONY: all
all: build run
run:
	./$(EXECUTABLE)

build: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) -o $@
clean:
	rm -rf $(BUILDDIR) $(EXECUTABLE)
