CC = gcc
CFLAGS = -O2

all: .exe

data.o: tools.h tools.c
	$(CC) -c $(CFLAGS) main.c

.exe: tools.o main.c
	$(CC) -c $(CFLAGS) main.c
	$(CC) -o main.exe main.o tools.o

clean: 
	rm *.o 
	rm *.exe
	