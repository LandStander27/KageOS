#include "port.h"

char convert(int c) {
	char keyboard_rows[4][10] = { "1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm" };
	if (c >= 0x02 && c <= 0x0B) {
		return keyboard_rows[0][c-0x02];
	} else if (c >= 0x10 && c <= 0x19) {
		return keyboard_rows[1][c-0x10];
	} else if (c >= 0x1E && c <= 0x26) {
		return keyboard_rows[2][c-0x1E];
	} else if (c >= 0x2C && c <= 0x32) {
		return keyboard_rows[3][c-0x2C];
	}

	switch (c) {
		case 0x39:
			return ' ';
		case 0x1C:
			return '\n';
		default:
			return 0x3;
	}

}

enum Action {
	Press,
	Release,
};

struct Keycode {
	int code;
	enum Action action;
	char character;
};

struct Keycode get_input() {

	struct Keycode key;

	int code = 0;
	while ((code = inb(0x60)) != 0) {
		if (code > 0) {
			key.code = code;
			if ((code & 128) == 128) {
				key.action = Release;
			} else {
				key.action = Press;
			}
			key.character = convert(code);
			return key;
		}
	}

	key.code = code;
	if ((code & 128) == 128) {
		key.action = Release;
	} else {
		key.action = Press;
	}
	key.character = convert(code);
	return key;
}

struct Keycode get_input_instant() {

	struct Keycode key;

	int code = inb(0x60);

	key.code = code;
	if ((code & 128) == 128) {
		key.action = Release;
	} else {
		key.action = Press;
	}
	key.character = convert(code);
	return key;
}
