#include "icmp.h"

static uint16_t ident = 0;

struct icmp_packet
icmp_echo_packet(void)
{
	struct icmp_packet packet;
	uint32_t sum;

	packet.type = 8;  /* echo message */
	packet.code = 0;
	packet.ident = ++ident;
	packet.seq = 1;
	packet.data = 0x4a55414e;  /* JUAN */

	/* internet checksum */
	sum = ((packet.type << 8) | packet.code) + packet.ident + packet.seq + packet.data;
	sum = (sum & 0xffff) + (sum >> 16);
	packet.checksum = ~sum;

	return packet;
}
