CC = gcc
CFLAGS = -Wall -Wextra -std=c23 -Iinclude

TARGET = logiccore.exe

SRC = src/main.c src/menu.c	src/circuit.c src/gate.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)