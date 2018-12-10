[GLOBAL _asm_gdt_flush]    ; Allows the C code to call _asm_gdt_flush().

_asm_gdt_flush:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]  ; Get the first argument.
    lgdt [eax]        ; Load the new GDT pointer

    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax        ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
    mov esp, ebp
    pop ebp
    ret

[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
    lidt [eax]        ; Load the IDT pointer.
    ret
