all: kernel.elf

FILES = bootloader.asm \
 				kernel.c \
				screen.c \
				timer.c \
				asm.c \
				descriptor_tables.c \
				isr.c \
				interrupt.asm \
				printk.c \
				drivers/keyboard/ps2.c \
				gdt.asm \
				string.c \
				mm/paging.c \
				mm/kmem.c \
				mm/panic.c \
				mm/kheap.c \
				switch_thread.asm \
				thread.c \
				scheduler.c \
				tests/multithreading_test.c \
				tests/heap_test.c

ASM_FILES = $(filter %.asm, $(FILES))
C_FILES   = $(filter %.c, $(FILES))

O_FILES = $(FILES:.c=.o)
O_FILES := $(O_FILES:.asm=.o)

CFLAGS= -Iinclude \
 		-g \
		-gdwarf-4\
		-Wall \
		-Wextra \
		-m32 \
		-std=c89 \
		-pedantic-errors \
		-fno-pie \
		-fno-stack-protector \
		-nostdlib \
		-ffreestanding \
		-fno-builtin \
		-mno-red-zone

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm -f elf32 $< -o $@

kernel.elf: $(O_FILES)
	ld -o $@ ${O_FILES} -Tlinker.ld --oformat elf32-i386 -m elf_i386

clean:
	find -name "*.o"   -delete
	find -name "*.elf" -delete
