# KawaiiOS
## What is KawaiiOS?
KwaiiOS is a hobby A 32-bit operating system for educational purposes meant to be UNIX-like but with its own kernel.
## How to compile annd run it?
### Requirments:
1. GCC
2. GNU Make
3. QEMU

### Compiling
`$ make`
### Running
`$ make && qemu-system-i386 -machine q35 -fda disk.img`