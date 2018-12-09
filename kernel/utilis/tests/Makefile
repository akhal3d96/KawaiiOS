SRC = $(wildcard *.c)
TAR = $(SRC:.c=.bin)

all: $(TAR)

%.bin: %.c
	SRC=$<
	gcc -DTEST -isystem ../../include -I ../../../minunit ../$(SRC:_test.c=.c) -lrt -lm $< -o $@

clean:
	rm *.bin