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

		if (key.character == 0x3 && key.code != 0x0E) {
			valid_press = false;
		}

		if (valid_press) {
			if (key.code == 0x0E) {
				if (command_len != 0) {
					write(pos, " ");
					left(pos, 2);
					write(pos, "_");
					left(pos, 1);

					cmd[command_len-1] = '\0';
					command_len--;
				}
			} else {
				str[0] = key.character;
				write(pos, str);
				write(pos, "_");
				left(pos, 1);

				cmd[command_len] = key.character;
				command_len++;
			}
		}
	}
}

int run_command(char *cmd, int *pos, char error[]) {

	int cmd_len = str_len(cmd);
	int code = 0;

	if (starts_with(cmd, "echo")) {
		if (cmd_len > 5) {
			// char *echoed;
			// strip_prefix(cmd, 5, echoed);

			// write(pos, echoed);
			for (int i = 5; i < str_len(cmd); i++) {
				char a[2];
				a[0] = cmd[i];
				a[1] = '\0';
				write(pos, a);
			}
		}
	} else if (starts_with(cmd, "clear")) {
		*pos = 0;
		clear_screen();
		write(pos, "KageOS\n\n");

		return code;
	} else {
		write(pos, "No command found with that name");
	}

	write(pos, "\n");

	return code;
}

int kernel_main(char error[]) {

	clear_screen();

	int pos = 0;
	write(&pos, "KageOS\n\n");

	char *command;

	while (true) {
		get_command(command, &pos);

		if (str_len(command) == 0) {
			continue;
		}

		int code = run_command(command, &pos, error);

		if (code != 0) {
			return code;
		}

		command[0] = '\0';

	}

	return 0;
}

void kernel_entry() {
	char error[100] = "No error message";
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
