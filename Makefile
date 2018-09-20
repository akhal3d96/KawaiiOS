all: os-image

kernel.o:
	gcc -Wall -m32 -fno-pie -nostdlib -ffreestanding -c kernel/kernel.c -o kernel/kernel.o
	gcc -Wall -m32 -fno-pie -nostdlib -ffreestanding -c kernel/low_level.c -o kernel/low_level.o
	gcc -Wall -m32 -fno-pie -nostdlib -ffreestanding -c kernel/screen.c -o kernel/screen.o

	
kernel.bin: kernel.o
	ld -o kernel/$@ -e kernel_main -Ttext 0x1000 kernel/kernel.o kernel/low_level.o kernel/screen.o -Tkernel/linker.ld --oformat binary -m elf_i386

# kernel.bin: kernel.oprint characters only no strings
	# ld -o kernel/$@ -e kernel_main -Ttext 0x1000 kernel/kernel.o kernel/low_level.o kernel/screen.o -T kernel/linker.ld -m elf_i386

os-image: kernel.bin
	make -C bootloader
	dd conv=notrunc if=kernel/$< of=disk.img bs=512 count=15 seek=1

clean:
	rm kernel/*.bin kernel/*.o
	rm bootloader/bootloader
	rm disk.img
