../bin/main: main.c icmp.c icmp.h
	mkdir -p ../bin
	gcc -Wall -Wextra -Wpedantic -std=iso9899:1999 -o ../bin/main main.c icmp.c

run: ../bin/main
	./../bin/main

clean:
	rm -f ../bin/main
