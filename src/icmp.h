#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

struct icmp_packet {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t ident;
	uint16_t seq;
	void *data;
};

/*
 * Internet checksum is the one's complement of the one's complement sum of
 * the fields. The fields are 16-bit words. A 32-bit variable was used to
 * avoid overflows and carry operations. The loop folds the 32-bit variable
 * to 16-bits, to return a 16-bit checksum. The implemention and the loop
 * were derived from the RFC 1071 "Computing the Internet Checksum".
 * It is possible that my understanding and implentation were not correct.
 * I'll check the implementation later, once I assign an identifier and a
 * sequence number to the packet.
 */
uint16_t icmp_checksum(struct icmp_packet packet)
{
	uint32_t sum = ~(packet.type + packet.code);
	sum += ~packet.ident;
	sum += ~packet.seq;

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}

#endif	/* ICMP_H */
