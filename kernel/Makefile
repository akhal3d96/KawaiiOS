SRC_FILES = $(shell find -name "*.c" -or -name "*.asm")

O_FILES = $(SRC_FILES:.c=.o)
O_FILES := $(O_FILES:.asm=.o)

O_FILES_SORTED = kernel.o screen.o timer.o asm.o \
descriptor_tables.o isr.o interrupt.o printk.o drivers/keyboard/ps2.o gdt.o \
string.o

CFLAGS=-Iinclude -Wall -m32 -std=c89 -pedantic-errors -fno-pie \
-fno-stack-protector -nostdlib -ffreestanding

all: kernel.bin


%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

kernel.bin: ${O_FILES}
	ld -o $@ -e kernel_main -Ttext 0x1000 ${O_FILES_SORTED} -Tlinker.ld --oformat binary -m elf_i386

clean:
	find -name "*.o"   -delete
	find -name "*.bin" -delete
	find -name "*.img" -delete
