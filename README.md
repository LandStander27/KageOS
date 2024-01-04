### KageOS
- Extremely simple OS made from scratch.

#### Getting the latest ISO
1. Go to the Actions tab
2. Select the latest workflow run
3. Click on the "KageOS" file, below "Artifacts"

#### Building
1. `sudo apt install make nasm gcc xorriso qemu qemu-system-x86 qemu-system-i386 virtualbox git`
2. `git clone https://github.com/LandStander27/KageOS`
3. `cd KageOS`
4. `make`
5. The ISO and BIN should be located under ./bin