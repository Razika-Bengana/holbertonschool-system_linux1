section .text
global asm_strcspn

asm_strcspn:
    push    rbp                    ; Prologue: Save the base pointer
    mov     rbp, rsp               ; Set up the base pointer

    mov     QWORD [rbp - 24], rdi  ; Store str parameter on the stack
    mov     QWORD [rbp - 32], rsi  ; Store reject parameter on the stack
    mov     QWORD [rbp - 8], 0     ; Initialize count to 0
    mov     QWORD [rbp - 16], 0    ; Initialize index to 0

    jmp     base_loop              ; Jump to the base loop

cmp_loop_r:
    mov     rax, QWORD [rbp - 32]  ; Load reject pointer
    mov     QWORD [rbp - 16], rax  ; Store reject pointer in index

    jmp     tmp_loop               ; Jump to the temporary loop

ini_t:
    add     QWORD [rbp - 16], 1    ; Increment index
tmp_loop:
    mov     rax, QWORD [rbp - 16]  ; Load index
    movzx   eax, BYTE [rax]        ; Dereference index
    test    al, al                 ; Check if index character is null ('\0')
    je      cmp_tmp                ; If null, jump to compare temporary

    mov     rax, QWORD [rbp - 16]  ; Load index
    movzx   edx, BYTE [rax]        ; Dereference index
    mov     rax, QWORD [rbp - 24]  ; Load str pointer
    movzx   eax, BYTE [rax]        ; Dereference str
    cmp     dl, al                 ; Compare index character with str character
    jne     ini_t                  ; If not equal, jump to increment index

cmp_tmp:
    mov     rax, QWORD [rbp - 16]  ; Load index
    movzx   eax, BYTE [rax]        ; Dereference index
    test    al, al                 ; Check if index character is null ('\0')
    je      plus_var               ; If null, jump to increment count

    jmp     return                 ; Jump to the return section

plus_var:
    add     QWORD [rbp - 8], 1     ; Increment count
    add     QWORD [rbp - 24], 1    ; Increment str pointer

base_loop:
    mov     rax, QWORD [rbp - 24]  ; Load str pointer
    movzx   eax, BYTE [rax]        ; Dereference str
    test    al, al                 ; Check if str character is null ('\0')
    jne     cmp_loop_r             ; If not null, jump to compare loop

return:
    mov     rax, QWORD [rbp - 8]   ; Load count value

    pop     rbp                    ; Epilogue: Restore the base pointer
    ret                            ; Return from the function
