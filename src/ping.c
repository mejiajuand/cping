#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include "ping.h"

void
ping(char addr[])
{
	int s, sockfd;
	struct addrinfo hints, *res;
	struct icmp_packet packet;
	ssize_t bytes;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = 1;
	hints.ai_flags = 0;

	s = getaddrinfo(addr, NULL, &hints, &res);
	
	if (s != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (sockfd == -1) {
		fprintf(stderr, "socket(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	s = connect(sockfd, res->ai_addr, res->ai_addrlen);

	if (s == -1) {
		fprintf(stderr, "connect(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	packet = icmp_echo_packet();

	printf("Pinging %s... ", addr);
	bytes = sendto(sockfd, &packet, sizeof(packet), 0, res->ai_addr, res->ai_addrlen);
	printf("received %zu bytes\n", bytes);
	show_packet(&packet);

	freeaddrinfo(res);
	close(sockfd);
}

void
show_packet(const struct icmp_packet *packet)
{
	printf("--- Packet Information ---\n");
	printf("Type: %u\n", packet->type);
	printf("Code: %u\n", packet->code);
	printf("Checksum: %#06x\n", packet->checksum);
	printf("Identifier: %u\n", packet->ident);
	printf("Sequence: %u\n", packet->sequence);
	printf("Data: %#08x\n", packet->data);
	printf("Size: %zu\n", sizeof(*packet));
}
