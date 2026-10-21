../bin/main: main.c icmp.c icmp.h ping.c ping.h
	mkdir -p ../bin
	gcc -Wall -Wextra -Wpedantic -o ../bin/main main.c icmp.c ping.c

run: ../bin/main
	./../bin/main

clean:
	rm -f ../bin/main
