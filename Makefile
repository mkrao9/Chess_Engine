CC = g++
CFLAGS = -O3 -Wall

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe