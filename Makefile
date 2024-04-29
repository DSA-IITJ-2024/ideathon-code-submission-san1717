CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = main.c trie.c support.c
OUT = lexical_analyzer
INFILE = input.txt

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

run: all
	./$(OUT) $(INFILE)

clean:
	rm -f $(OUT)