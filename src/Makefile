

#testing makefile 
CC = g++ 
CFLAGS  = -g -o -Wall -O3 
OBJFILES = main.o board.o move.o attack_set.o
TARGET = ../engine

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
