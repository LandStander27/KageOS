#include "kernel.h"

int kernel_main() {
	return 0;
}

void kernel_entry() {
	int return_code = kernel_main();
	while (true) {  }
}
