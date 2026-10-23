#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include "icmp.h"
#include "ping.h"

void
ping(char addr[])
{
	int i, s, sockfd;
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

	printf("Pinging %s with %zu bytes of data\n", addr, sizeof(packet));
	for (i = 0; i < 4; i++) {
		packet = icmp_echo_packet();
		bytes = sendto(sockfd, &packet, sizeof(packet), MSG_CONFIRM, res->ai_addr, res->ai_addrlen);

		if (bytes == -1) {
			fprintf(stderr, "sendto(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		printf("Received %zu bytes from %s\n", bytes, addr);
	}
	printf("\n--- %s ping statistics ---\n", addr);
	printf("%u packets transmitted, %u packets received, %.0f%% packet loss\n",
			i, packet.sequence, (1 - ((double)packet.sequence / i)) * 100);
	freeaddrinfo(res);
	close(sockfd);
}
