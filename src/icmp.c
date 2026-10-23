#include <arpa/inet.h>
#include <stdio.h>

#include "icmp.h"

static uint16_t ident = 1;
static uint16_t sequence = 1;

struct icmp_packet
icmp_echo_packet(void)
{
	struct icmp_packet packet;
	packet.type = 8; /* echo request */
	packet.code = 0;
	packet.ident = ident++;
	packet.sequence = sequence++;
	packet.data = htonl(0x41414141); /* AAAA */
	checksum(&packet);
	return packet;
}

void
checksum(struct icmp_packet *packet)
{
	uint32_t sum;
	sum = htons((packet->type << 8) | packet->code);
	sum = sum + packet->ident + packet->sequence + packet->data;
	sum = (sum & 0xffff) + (sum >> 16);
	packet->checksum = ~sum;
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
