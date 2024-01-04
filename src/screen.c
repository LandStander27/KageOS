#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include "string.h"

void left(int *pos, int amount) {
	*pos -= 2*amount;
}

void right(int *pos, int amount) {
	*pos += 2*amount;
}

void write(int *pos, char *str) {
	volatile char *video = (volatile char*)0xB8000;
	
	for (int i = 0; i < *pos; i++) {
		*video++;
	}

	while(*str != 0) {
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
		right(pos, 1);
	}
}

void write_to(int pos, char *str) {
	volatile char *video = (volatile char*)0xB8000;

	for (int i = 0; i < pos; i++) {
		*video++;
	}

	while(*str != 0) {
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
		right(&pos, 1);
	}
}

void clear_screen() {
	volatile char *video = (volatile char*)0xB8000;

	for (int i = 0; i < 1000; i++) {
		*video++ = ' ';
		*video++ = 15;
	}
}
