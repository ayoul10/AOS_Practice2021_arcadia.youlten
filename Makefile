CC=g++
CFLAGS= -I -g -Wall -Wextra -ggdb3 -lpthread
DEPS = FileManager.h FileManager.cpp Fat16.cpp Fat16.h main.cpp Disk.h Errors.h Errors.c Ext2.cpp Ext2.h
OBJ = main.o FileManager.o Fat16.o Errors.o Ext2.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shooter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	-rm edit $(objects)
