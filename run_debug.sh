#!/usr/bin/env bash
make
qemu-system-i386 -d cpu_reset\
                 -boot d \
                 -enable-kvm \
                 -kernel kernel/kernel.elf \
                 -m 16 -S -gdb tcp::8080 &
gdb -q