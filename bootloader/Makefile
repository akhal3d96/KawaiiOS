all: bootloader.bin

bootloader.bin: bootloader.asm
	nasm -f bin $^ -o $@

clean:
	rm *.bin