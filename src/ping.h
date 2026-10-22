#ifndef PING_H
#define PING_H

#include "icmp.h"

void ping(char[]);
void show_packet(const struct icmp_packet*);

#endif	/* PING_H */
