CC=gcc
CFLAGS=-Wall -fno-stack-protector -g

OBJ_FILES=$(patsubst %.c, %.o, $(wildcard *.c))

run: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf run.gitignoreme *.o

