define hook-stop

    printf "[%4x:%4x] ", $cs, $eip

    x/i $cs*16+$eip

end
file kernel/kernel.elf
set disassembly-flavor intel
set architecture i8086
set architecture i8086
target remote localhost:8080
