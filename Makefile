CC = g++
CFLAGS = -Wall -g

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe