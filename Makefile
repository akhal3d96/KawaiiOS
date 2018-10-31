FIND_INDENT_PARAMS=-exec indent -linux {} \;

all: os-image

kernel.elf:
	make -C kernel
	
bootloader.elf:
	make -C bootloader

os-image: bootloader.elf kernel.elf
	cp kernel/kernel.elf iso/boot/
	mkisofs -R 							 \
			-b boot/grub/stage2_eltorito \
    		-no-emul-boot                \
    		-boot-load-size 4            \
    		-A os                        \
    		-input-charset utf8          \
    		-quiet                       \
    		-boot-info-table             \
    		-o kawaiios.iso              \
    		iso

clean:
	find -name "*.o"   -delete
	find -name "*.*~"  -delete
	find -name "*.elf" -delete
	rm *.iso
beautify:
	find -name "*.c" ${FIND_INDENT_PARAMS}
	find -name "*.h" ${FIND_INDENT_PARAMS}