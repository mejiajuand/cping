#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <arpa/inet.h>

#include <unistd.h>
#include <errno.h>

#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include "icmp.h"
#include "ping.h"

void
ping(char data[])
{
	int s, fd;
	ssize_t bytes_recv;
	struct icmp_packet packet;
	struct addrinfo hints, *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = 1;
	hints.ai_flags = 0;

	s = getaddrinfo(data, NULL, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "ERROR: getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (fd == -1) {
		fprintf(stderr, "ERROR: socket(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	s = connect(fd, result->ai_addr, result->ai_addrlen);
	if (s == -1) {
		fprintf(stderr, "ERROR: connect(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	packet = icmp_echo_packet();
	packet.checksum = ntohs(packet.checksum);
	bytes_recv = sendto(fd, &packet, sizeof(packet), 0, result->ai_addr, result->ai_addrlen);

	printf("--- Packet Information ---\n");
	printf("Type: %u\n", packet.type);
	printf("Code: %u\n", packet.code);
	printf("Checksum: %#06x\n", packet.checksum);
	printf("Identifier: %u\n", packet.ident);
	printf("Sequence: %u\n", packet.seq);
	printf("Data: %s\n", &packet.data);

	if (bytes_recv == -1) {
		fprintf(stderr, "ERROR: sendmsg(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);

	printf("Received %zu bytes\n", bytes_recv);

	s = close(fd);
	if (s == -1) {
		fprintf(stderr, "ERROR: close(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
