CC=gcc
CFLAGS=-I/usr/include/raylib -lraylib -lm -lpthread -ldl -lrt -lX11
SRC=src/main.c
OBJ=$(SRC:.c=.o)
EXEC=game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)