CC=g++
CFLAGS= -I -g -Wall -Wextra -ggdb3 -lpthread
DEPS = FileManager.h FileManager.cpp Fat16.cpp Fat16.h main.cpp Disk.h Errors.h Errors.c
OBJ = main.o FileManager.o Fat16.o Errors.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shooter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	-rm edit $(objects)
