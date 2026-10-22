#include <arpa/inet.h>

#include "icmp.h"

static uint16_t ident = 1;

struct icmp_packet
icmp_echo_packet(void)
{
	struct icmp_packet packet;
	packet.type = 8; /* echo request */
	packet.code = 0;
	packet.ident = ident++;
	packet.sequence = 0;
	packet.data = htonl(0x41414141); /* AAAA */
	checksum(&packet);
	return packet;
}

void
checksum(struct icmp_packet *packet)
{
	uint32_t sum;
	sum = htons((packet->type << 8) | packet->code);
	sum = sum + 0 + packet->ident + packet->sequence + packet->data;
	sum = (sum & 0xffff) + (sum >> 16);
	packet->checksum = ~sum;
}
