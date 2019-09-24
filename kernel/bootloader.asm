
MBOOT_PAGE_ALIGN    equ 1<<0        ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1        ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002  ; Multiboot Magic value

MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                    ; All instructions should be 32-bit.

section .mboot
align 4
dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                            ; 4-byte boundary in your kernel file
dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct

section .bss
align 16
stack_end:
    resb 16384 ; 16 KiB Stack
stack_start:

section .text
global start:function (start.end - start)
[EXTERN kernel_main]
start:
    ; Set-up the stack
    mov esp, stack_start
    ; Load multiboot information:
    push ebx

    ; Execute the kernel:
    cli
    call kernel_main
    jmp $
.end: