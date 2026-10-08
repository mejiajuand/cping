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

#endif	/* ICMP_H */
