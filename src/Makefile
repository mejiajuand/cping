CC=clang

../bin/ping: $(wildcard *.[c|h])
	mkdir -p ../bin
	$(CC) -Wall -Wextra -Wpedantic --std=iso9899:1999 -o ../bin/ping main.c icmp.c ping.c

run: ../bin/ping
	./../bin/ping

clean:
	rm -f ../bin/ping
