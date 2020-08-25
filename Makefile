CC = g++
CFLAGS = -c -Wall

all: main

main: main.o Movement.o
	$(CC) main.o Movement.o -o main

zzz_main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

movement.o: Movement.cpp
	$(CC) $(CFLAGS) Movement.cpp

clean:
	rm -f *.o .~
