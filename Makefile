CC = g++
CFLAGS = -O3 -g 

all: 
	$(CC) $(CFLAGS) src/*.cpp -o engine.exe
