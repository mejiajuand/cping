#include <stdio.h>

#include "icmp.h"

void
display_icmp_packet(struct icmp_packet *packet)
{
	printf("Packet Type: %u\n", packet->type);
	printf("Packet Code: %u\n", packet->code);
	printf("Packet Checksum: %#06x (LE)\n", packet->checksum);
	printf("Packet Identifier: %u\n", packet->ident);
	printf("Packet Sequence Number: %u\n", packet->seq);
	printf("Packet Data: %p\n", packet->data);
	printf("Packet Size: %zu bytes\n", sizeof(packet));
}

int
main(void)
{
	struct icmp_packet p = icmp_echo_packet();
	struct icmp_packet q = icmp_echo_packet();
	printf("--- First Echo Packet ---\n");
	display_icmp_packet(&p);
	printf("\n--- Second Echo Packet --- \n");
	display_icmp_packet(&q);
	return 0;
}
