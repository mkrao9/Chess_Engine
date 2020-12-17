CC = g++
CFLAGS = -Wall -g -pg

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe