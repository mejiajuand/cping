../bin/main: main.c
	mkdir -p ../bin
	gcc -Wall -Wextra -Wpedantic -std=iso9899:1999 -o ../bin/main main.c

run: ../bin/main
	./../bin/main

clean:
	rm -f ../bin/main
