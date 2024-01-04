#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include "kernel.h"
#include "bool.h"
#include "types.h"
#include "string.h"
#include "screen.h"
#include "keyboard.h"

void get_command(char *cmd, int *pos) {
	write(pos, "> _");
	left(pos, 1);

	{
		struct Keycode key = get_input_instant();
		while (key.character == '\n') {
			key = get_input_instant();
		}
	}

	int last_key = -1;
	int command_len = 0;

	char str[2] = { ' ', '\0' };

	while (true) {

		bool valid_press = false;

		struct Keycode key = get_input();

		if (key.action == Press) {
			if (last_key == -1) {
				last_key = key.code;
				valid_press = true;
			} else {
				if (last_key != key.code) {
					last_key = key.code;
					valid_press = true;
				}
			}
		} else {
			last_key = -1;
		}

		if (key.character == '\n') {
			write(pos, " \n");
			cmd[command_len] = '\0';
			return;
		}

		if (valid_press) {
			str[0] = key.character;
			write(pos, str);
			write(pos, "_");
			left(pos, 1);

			cmd[command_len] = key.character;
			command_len++;
			
		}

	}
}

int kernel_main(char *error) {

	clear_screen();

	int pos = 0;
	write(&pos, "KageOS\n\n");

	char *command;

	while (true) {
		get_command(command, &pos);

		if (str_len(command) == 0) {
			continue;
		}

		write(&pos, command);
		write(&pos, "\n");

		command[0] = '\0';

	}

	return 0;
}

void kernel_entry() {
	char *error = "No error message";
	int return_code = kernel_main(error);
	clear_screen();

	int pos = 0;
	write(&pos, "Error code: ");

	char *str;
	int_to_string(return_code, str);

	write(&pos, str);
	write(&pos, "\nError message: ");
	write(&pos, error);

	while (true) {  }
}
