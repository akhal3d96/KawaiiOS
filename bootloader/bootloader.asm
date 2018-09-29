; I don't know how to start this shit, yo, now
;
;        - Nas - N.Y State of Mind

bits 16     ; real-mode works in 16 bit

org 0x7c00  ; the code should located at this address because it's what the 
            ; BIOS loads first

KERNEL_OFFSET equ 0x1000 

start: jmp boot

boot:
    cli ; clear all interrupts
    cld
    
    ; mov bp, 0x9000          ; Set  the  stack.
    ; mov sp, bp

    mov SI, Stage0_msg
    call PrintString

    call LoadKernel

    call SwitchToPM
    
    jmp $


; load_kernel
LoadKernel:
    mov SI, KernelStatus        ; Print a message  to say we are  loading  the  kernel
    call  PrintString
    
    mov bx, KERNEL_OFFSET       ; Set -up  parameters  for  our  disk_load  routine , so
    mov dh, 20                  ; that we load  the  first  20  sectors (excluding
    mov dl, [BOOT_DRIVE]        ; the  boot  sector) from  the  boot  disk (i.e.  our
    
    call  DiskLoad              ; kernel  code) to  address  KERNEL_OFFSET

EnableA20:
    pusha
    in al, 0x92
    or al, 2    
    out 0x92, al
    popa
    ret

; load DH  sectors  to ES:BX from  drive  DL
DiskLoad:
    push dx         ; Store  DX on  stack  so  later  we can  recall
                    ; how  many  sectors  were  request  to be read ,
                    ; even if it is  altered  in the  meantime
    
    mov ah, 0x02    ; BIOS  read  sector  function
    mov al, dh      ; Read DH  sectors
    mov ch, 0x00    ; Select  cylinder 0
    mov dh, 0x00    ; Select  head 0
    
    mov cl, 0x02    ; Start  reading  from  second  sector (i.e.
                    ; after  the  boot  sector)
    int 0x13        ; BIOS  interrupt
    jc  DiskError  ; Jump if error (i.e.  carry  flag  set)
    pop dx          ; Restore  DX from  the  stack
    cmp dh, al      ; if AL (sectors  read) != DH (sectors  expected)
    jne  DiskError ; display  error  message
    ret

DiskError:
    mov SI, DISK_ERROR_MSG
    call  PrintString
    jmp $

%include "io.asm"
%include "gdt.asm"
%include "protected-mode.asm"
%include "io-pm.asm"

Stage0_msg db 'KawaiiOS Bootloader (Stage 0)', 0x0D, 0xA, 0
Stage1_msg db 'KawaiiOS Bootloader (Stage 1)', 0x0D, 0xA, 0

A20 db 'A20 line was enabled', 0


DISK_ERROR_MSG   db "Disk  read  error!", 0
BOOT_DRIVE db 0

KernelStatus db 'The Sohila Kernel was loaded', 0x0D, 0xA, 0

times 510 - ( $ - $$) db 0 ; the size of bootloader should be 512 byte
                           ; so we are filling the remaining bytes with 0's

dw 0xAA55                  ; the bootloader should return this value 
                           ; so that the BIOS mark it as valid