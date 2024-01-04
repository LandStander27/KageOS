#ifndef PORT_H
#define PORT_H

#include "types.h"

uint8 inb(uint16 port);
void outb(uint16 port, uint8 data);

#endif