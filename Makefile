
CC = gcc

CFLAGS = -O2 -lSDL2 -lSDL2main -lSDL2_ttf

all: bin

bin: main.o
	$(CC) $(CFLAGS) main.o -o bin

main.o: main.c
	$(CC) $(CFLACGS) -c main.c

clean:
	rm -f *.o





