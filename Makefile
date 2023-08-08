
CC = gcc

CFLAGS = -O2 -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

all: bin

bin: main.o functions.o
	$(CC) $(CFLAGS) main.o functions.o -o bin

main.o: main.c
	$(CC) $(CFLACGS) -c main.c

functions.o: functions.c
	$(CC) $(CFLACGS) -c functions.c

clean:
	rm -f *.o





