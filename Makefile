CC = g++
CFLAGS = -Wall -O3

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe