#include <stdio.h>

#include "icmp.h"

void
display_icmp_packet(struct icmp_packet *packet)
{
	printf("Packet Type: %u\n", packet->type);
	printf("Packet Code: %u\n", packet->code);
	printf("Packet Checksum: %#06x\n", packet->checksum);
	printf("Packet Identifier: %u (%#06x)\n", packet->ident, packet->ident);
	printf("Packet Sequence Number: %u\n", packet->seq);
	printf("Packet Data: %p\n", (void*)packet->data);
	printf("Packet Size: %zu bytes\n", sizeof(packet));
}

int
main(void)
{
	struct icmp_packet p = icmp_echo_packet();
	struct icmp_packet q = icmp_echo_packet();
	printf("--- First Packet ---\n");
	display_icmp_packet(&p);
	printf("\n--- Second Packet --- \n");
	display_icmp_packet(&q);
	return 0;
}
