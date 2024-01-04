#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include "kernel.h"
#include "bool.h"
#include "string.h"

uint8 inb(uint16 port) {
	uint8 ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
	return ret;
}

void outb(uint16 port, uint8 data) {
	asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

void write(int *pos, char *str) {
	volatile char *video = (volatile char*)0xB8000;
	
	for (int i = 0; i < *pos; i++) {
		*video++;
	}

	while(*str != 0)
	{
		char a = *str++;
		if (a == '\n') {
			int amount_to_new = 160 - (*pos % 160);
			for (int i = 0; i < amount_to_new; i++) {
				*video++;
			}
			*pos += amount_to_new;
			continue;
		}
		*video++ = a;
		*video++ = 15;
		*pos += 2;
	}
}

void write_to(int pos, char *str) {
	volatile char *video = (volatile char*)0xB8000;

	for (int i = 0; i < pos; i++) {
		*video++;
	}

	while(*str != 0)
	{
		char a = *str++;
		if (a == '\n') {
			int amount_to_new = 160 - (pos % 160);
			for (int i = 0; i < amount_to_new; i++) {
				*video++;
			}
			pos += amount_to_new;
			continue;
		}
		*video++ = a;
		*video++ = 15;
		pos += 2;
	}
}

int kernel_main() {

	int pos = 0;
	write(&pos, "KageOS\n\n");

	return 0;
}

void kernel_entry() {
	int return_code = kernel_main();
	while (true) {  }
}
