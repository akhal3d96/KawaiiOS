all: bootloader

bootloader: bootloader.asm
	nasm -f elf32 $^ -o $@.o
		
clean:
	rm *.elf *.o