#include <stdio.h>

#include "icmp.h"

int
main(void)
{
	struct icmp_packet p = { 0 };
	p.type = 8;	/* echo request */
	p.checksum = icmp_checksum(p);

	printf("Packet Type: %u\n", p.type);
	printf("Packet Code: %u\n", p.code);
	printf("Packet Checksum: %u\n", p.checksum);
	printf("Packet Identifier: %u\n", p.ident);
	printf("Packet Sequence: %u\n", p.seq);
	printf("Packet Data: %p\n", p.data);
	printf("Packet Size: %zu bytes\n", sizeof(p));
	return 0;
}
