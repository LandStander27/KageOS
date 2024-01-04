#ifndef KEYBOARD_H
#define KEYBOARD_H

enum Action {
	Press,
	Release,
};

struct Keycode {
	int code;
	enum Action action;
	char character;
};

char convert(int c);
struct Keycode get_input();
struct Keycode get_input_instant();

#endif