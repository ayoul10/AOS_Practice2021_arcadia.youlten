CC=gcc
CFLAGS=-I.
DEPS = errors.h
OBJ = errors.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)