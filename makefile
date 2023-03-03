cc = gcc
CFLAGS = -Wall -Werror -std=gnu11
all: wc.c

wc: wc.c
	$(CC) $(CFLAGS) -o wc wc.c

clean:
	rm -f wc