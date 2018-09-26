CFLAGS=-Wall -m32 -fno-pie -nostdlib -ffreestanding

all: os-image

kernel.o:
	gcc ${CFLAGS} -c kernel/kernel.c -o kernel/kernel.o
	gcc ${CFLAGS} -c kernel/low_level.c -o kernel/low_level.o
	gcc ${CFLAGS} -c kernel/screen.c -o kernel/screen.o
	gcc ${CFLAGS} -c kernel/timer.c -o kernel/timer.o
	
	gcc ${CFLAGS} -c kernel/common.c -o kernel/common.o
	gcc ${CFLAGS} -c kernel/descriptor_tables.c -o kernel/descriptor_tables.o
	gcc ${CFLAGS} -c kernel/isr.c -o kernel/isr.o

	nasm -f elf32 kernel/gdt.s -o kernel/gdt.o 
	nasm -f elf32 kernel/interrupt.s -o kernel/interrupt.o
	
	

	
kernel.bin: kernel.o
	ld -o kernel/$@ -e kernel_main -Ttext 0x1000 kernel/kernel.o kernel/low_level.o kernel/screen.o kernel/timer.o kernel/common.o  kernel/descriptor_tables.o kernel/isr.o kernel/interrupt.o kernel/gdt.o  -Tkernel/linker.ld --oformat binary -m elf_i386
#kernel/isr.o kernel/descriptor_tables.o kernel/common.o kernel/gdt.o kernel/interrupt.o
# kernel.bin: kernel.oprint characters only no strings
	# ld -o kernel/$@ -e kernel_main -Ttext 0x1000 kernel/kernel.o kernel/low_level.o kernel/screen.o -T kernel/linker.ld -m elf_i386

os-image: kernel.bin
	make -C bootloader
	dd conv=notrunc if=kernel/$< of=disk.img bs=512 count=20 seek=1

clean:
	rm kernel/*.bin kernel/*.o
	rm bootloader/bootloader
	rm disk.img
