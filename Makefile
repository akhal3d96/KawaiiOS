FIND_INDENT_PARAMS=-exec indent -linux {} \;

all: os-image

kernel.elf:
	make -C kernel
os-image: kernel.elf
	cp kernel/kernel.elf isofiles/boot/
	grub-mkrescue -o kawaiios.iso isofiles
	
clean:
	find -name "*.o"   -delete
	find -name "*.*~"  -delete
	find -name "*.elf" -delete
	rm *.iso || true 
format:
	find -name "*.c" ${FIND_INDENT_PARAMS}
	find -name "*.h" ${FIND_INDENT_PARAMS}