# KawaiiOS
## What is KawaiiOS?
KwaiiOS is a hobby A 32-bit operating system for educational purposes meant to be UNIX-like but with its own kernel. It's tested on an emulation of Intel Q35 chipset.

<p align="center">
<img src="https://raw.githubusercontent.com/nemoload/KawaiiOS/master/screenshots/screenshot1.png">
</p>

## Memory map
* ### Physical memory
    | 0x00000 	| 0x07C00  	| BIOS                   	|
    |---------	|----------	|------------------------	|
    | 0x07C00 	| 0x07E00  	| Bootloader             	|
    | 0x07E00 	| 0x10000  	| UNUSED                 	|
    | 0x10000 	| 0x23CB8  	| Kernel                 	|
    | 0x23CB8 	| 0x100000 	| UNUSED + system reserved 	|

## How to compile annd run it?
### Requirments:
1. A running GNU/Linux environment
2. GCC
3. GNU Make
4. QEMU

### Compiling
`$ make`

This will compile the bootloader and the kernel, then it'll link the kernel components and finally will genrate a floppy disk image out of both the botloader and the kernel.
### Running
`$ qemu-system-i386 -machine q35 -fda disk.img`
## Note
The code of KawaiiOS is far from ready there's a lot of things that should be fixed and changed and the work is still in progress.
