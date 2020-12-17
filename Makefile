CC = g++
CFLAGS = -O3

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe
