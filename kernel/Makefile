all: kernel.elf 

SRC_FILES = $(shell find -name "*.c" -or -name "*.asm")

O_FILES = $(SRC_FILES:.c=.o)
O_FILES := $(O_FILES:.asm=.o)

O_FILES_SORTED = ../bootloader/bootloader.o kernel.o screen.o timer.o asm.o \
descriptor_tables.o isr.o interrupt.o printk.o drivers/keyboard/ps2.o gdt.o \
string.o mm/paging.o mm/kmem.o mm/panic.o mm/kheap.o switch_thread.o thread.o\
scheduler.o

CFLAGS=-Iinclude -g -gdwarf-4 -Wall -Wextra -m32 -std=c89 -pedantic-errors -fno-pie \
-fno-stack-protector -nostdlib -ffreestanding -fno-builtin -mno-red-zone

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

kernel.elf: ${O_FILES}
	ld -o $@ ${O_FILES_SORTED} -Tlinker.ld --oformat elf32-i386 -m elf_i386

clean:
	find -name "*.o"   -delete
	find -name "*.elf" -delete
