section .text
global asm_strpbrk

asm_strpbrk:
    push    rbp                    ; Prologue: Save the base pointer
    mov     rbp, rsp               ; Set up the base pointer

    mov     QWORD [rbp - 24], rdi  ; Store str parameter on the stack
    mov     QWORD [rbp - 32], rsi  ; Store accept parameter on the stack
    mov     QWORD [rbp - 8], 0     ; Initialize result pointer to 0

    jmp     base_loop              ; Jump to the base loop

cmp_loop:
    mov     rax, QWORD [rbp - 32]  ; Load accept pointer
    mov     QWORD [rbp - 8], rax   ; Store accept pointer in result pointer

    jmp     tmp_loop               ; Jump to the temporary loop

ini_t:
    add     QWORD [rbp - 8], 1     ; Increment result pointer
tmp_loop:
    mov     rax, QWORD [rbp - 8]   ; Load result pointer
    movzx   eax, BYTE [rax]        ; Dereference result pointer
    test    al, al                 ; Check if result character is null ('\0')
    je      cmp_tmp                ; If null, jump to compare temporary

    mov     rax, QWORD [rbp - 8]   ; Load result pointer
    movzx   edx, BYTE [rax]        ; Dereference result pointer
    mov     rax, QWORD [rbp - 24]  ; Load str pointer
    movzx   eax, BYTE [rax]        ; Dereference str
    cmp     dl, al                 ; Compare result character with str character
    jne     ini_t                  ; If not equal, jump to increment result pointer

cmp_tmp:
    mov     rax, QWORD [rbp - 8]   ; Load result pointer
    movzx   eax, BYTE [rax]        ; Dereference result pointer
    test    al, al                 ; Check if result character is null ('\0')
    je      plus_var               ; If null, jump to increment str pointer
    jmp     cmp_loop_aftr          ; Jump to the compare loop after the temporary loop

plus_var:
    add     QWORD [rbp - 24], 1    ; Increment str pointer

base_loop:
    mov     rax, QWORD [rbp - 24]  ; Load str pointer
    movzx   eax, BYTE [rax]        ; Dereference str
    test    al, al                 ; Check if str character is null ('\0')
    jne     cmp_loop               ; If not null, jump to compare loop

cmp_loop_aftr:
    cmp     QWORD [rbp - 8], 0     ; Compare result pointer to 0
    je      return_null            ; If result pointer is null, jump to return null

    mov     rax, QWORD [rbp - 8]   ; Load result pointer
    movzx   eax, BYTE [rax]        ; Dereference result pointer
    test    al, al                 ; Check if result character is null ('\0')
    je      return_null            ; If null, jump to return null

    mov     rax, QWORD [rbp - 24]  ; Load str pointer
    jmp     return                 ; Jump to the return section

return_null:
    mov     eax, 0                 ; Set return value to 0 (null)

return:
    pop     rbp                    ; Epilogue: Restore the base pointer
    ret                            ; Return from the function
