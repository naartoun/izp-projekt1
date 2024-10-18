CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror

.PHONY: clean pack run

main: tnine.c
	$(CC) $(CFLAGS) tnine.c -o tnine

main-debug: tnine.c
	$(CC) $(CFLAGS) -DDEBUG_PRINT=1 $^ -o "$@"

clean:
	rm -Rf *.o main odevzdani.tar.gz

pack:
	tar -czvf odevzdani.tar.gz ./*

run: main
	./tnine