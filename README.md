# KawaiiOS 
[![Build Status](https://travis-ci.com/nemoload/KawaiiOS.svg?branch=master)](https://travis-ci.com/nemoload/KawaiiOS)

## What is KawaiiOS?
KwaiiOS is a hobbyist 32-bit, uniprocessor, operating system made for educational purposes. Its final goal is to be a UNIX-like operating system. It's tested on an Intel Q35 chipset virtual machine. IT'S FULL OF BUGS.

<p align="center">
<img src="https://raw.githubusercontent.com/nemoload/KawaiiOS/master/screenshots/screenshot1.png">
</p>

## Known Issues
* Multiboot headers aren't being handled yet so you have to load the kernel elf file directly to 
qemu in order to load it.

* ¯\\\_(° ͜ʖ °)_/¯

## How to compile annd run it?
### Requirments:
1. A GNU/Linux environment
2. GCC (with cross-compiling)
3. NASM
4. GNU Make
5. QEMU. 
6. cdrtools

### Installing:
`$ sudo apt-get install nasm mkisofs gcc-multilib`
### Compiling:
`$ make  # Haven't expected that, have you?`
### Running:
`$ qemu-system-i386 -enable-kvm -d cpu_reset -boot d -kernel kernel/kernel.elf -m 16`

You can omitt the `-enable-kvm` parameter if you don't have KVM  or don't want to. Also the memory size is, for now, hard coded into the source code so changing the memory size from **16** in `-m 16` to anything else migh break up some stuff.

## Features:

#### Supported Archetictures:
- [x] Intel x86
- [ ] ARMv7-A
    

Archticture-depndent features:
- [ ] Multitasking
- [x] Multithreading

#### Kernel Features:
- [x] Monolithic design
- [ ] Virtual File System

#### Supported Devices:

- [x] PS/2 Keyboard



## Note
The code of KawaiiOS is far from ready there's a lot of things that should be fixed and changed and the work is still in progress.
