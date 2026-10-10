#include <stdlib.h>      /* malloc, NULL */

#include "icmp.h"

static uint16_t ident = 0;

struct icmp_packet
icmp_echo_packet(void)
{
	struct icmp_packet packet;
	packet.type = 8;  /* echo message */
	packet.code = 0;
	packet.ident = ++ident;
	packet.seq = 1;
	packet.data = NULL;

	/* internet checksum */
	packet.checksum = ~(~(packet.type + packet.code) + ~packet.ident + ~packet.seq);
	return packet;
}
