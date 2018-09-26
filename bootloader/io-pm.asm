bits  32
; Define  some  constants
VIDEO_MEMORY  equ 0xb8000
WHITE_ON_BLACK  equ 0x0f
; prints a null -terminated  string  pointed  to by EDX
PrintStringPM:
    pusha
    mov edx , VIDEO_MEMORY   ; Set  edx to the  start  of vid  mem.
PrintStringPM_loop:
    mov al, [ebx]            ; Store  the  char at EBX in AL
    mov ah, WHITE_ON_BLACK   ; Store  the  attributes  in AH
    or al, al                ; if (al == 0), at end of string , so
    jz PrintStringPM_done    ; jump to done
    mov [edx], ax            ; Store  char  and  attributes  at  current
                             ; character  cell.
    
    inc ebx                  ; Increment  EBX to the  next  char in  string.
    add edx , 2              ; Move to next  character  cell in vid  mem.
    jmp  PrintStringPM_loop  ; loop  around  to  print  the  next  char.

PrintStringPM_done :
    popa
    ret                      ; Return  from  the  function
