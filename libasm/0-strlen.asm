section .text
global asm_strlen

asm_strlen:
    xor rax, rax              ; Clear the rax register to use it as a counter

.loop:
    cmp byte [rdi + rax], 0   ; Compare the byte at [rdi + rax] with null terminator
    je .end                   ; If null terminator is found, jump to .end

    inc rax                   ; Increment the counter
    jmp .loop                 ; Jump back to .loop to process the next byte

.end:
    ret                       ; Return the value of the counter in rax
