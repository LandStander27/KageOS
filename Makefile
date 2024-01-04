run:
	mkdir -p temp
	mkdir -p bin

	as --32 boot/boot.s -o temp/boot.o
	gcc -m32 -Iinclude -c src/kernel.c -o temp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -Iinclude -c src/string.c -o temp/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -Iinclude -c src/screen.c -o temp/screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -Iinclude -c src/port.c -o temp/port.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -Iinclude -c src/keyboard.c -o temp/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ld -m elf_i386 -T boot/linker.ld temp/kernel.o temp/string.o temp/screen.o temp/port.o temp/keyboard.o temp/boot.o -o bin/KageOS.bin -nostdlib
	grub-file --is-x86-multiboot bin/KageOS.bin

	mkdir -p temp/isodir/boot/grub
	cp bin/KageOS.bin temp/isodir/boot/KageOS.bin
	cp boot/grub.cfg temp/isodir/boot/grub/grub.cfg
	grub-mkrescue -o bin/KageOS.iso temp/isodir

	qemu-system-x86_64 -cdrom bin/KageOS.iso

clean:
	rm -rf temp
