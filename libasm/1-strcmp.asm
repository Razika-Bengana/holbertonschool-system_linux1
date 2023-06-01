section .text
global asm_strcmp

asm_strcmp:
    push    rbp                      ; Prologue
    mov     rbp, rsp

    mov     QWORD [rbp - 8], rdi     ; Reserve space for s1 on stack
    mov     QWORD [rbp - 16], rsi    ; Reserve space for s2 on stack

    jmp     .s1_s2_loop_tests        ; Jump to the main loop

.inc_s1_s2:
    add     QWORD [rbp - 8], 1       ; Increment s1 pointer
    add     QWORD [rbp - 16], 1      ; Increment s2 pointer

.s1_s2_loop_tests:
    mov     rax, QWORD [rbp - 8]     ; Load character from s1
    movzx   eax, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)
    test    al, al                   ; Check if s1 reached null terminator
    je      .test_s1_gt_s2           ; Jump to test_s1_gt_s2 if s1 reached null terminator

    mov     rax, QWORD [rbp - 16]    ; Load character from s2
    movzx   eax, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)
    test    al, al                   ; Check if s2 reached null terminator
    je      .test_s1_gt_s2           ; Jump to test_s1_gt_s2 if s2 reached null terminator

    mov     rax, QWORD [rbp - 8]     ; Load character from s1
    movzx   edx, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    mov     rax, QWORD [rbp - 16]    ; Load character from s2
    movzx   eax, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    cmp     dl, al                   ; Compare characters
    je      .inc_s1_s2               ; Jump to inc_s1_s2 if characters are equal

.test_s1_gt_s2:
    mov     rax, QWORD [rbp - 8]     ; Load character from s1
    movzx   edx, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    mov     rax, QWORD [rbp - 16]    ; Load character from s2
    movzx   eax, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    cmp     dl, al                   ; Compare characters
    jle     .test_s1_lt_s2           ; Jump to test_s1_lt_s2 if s1 <= s2

    mov     eax, 1                   ; s1 > s2, set return value to 1
    jmp     .return                  ; Jump to return

.test_s1_lt_s2:
    mov     rax, QWORD [rbp - 8]     ; Load character from s1
    movzx   edx, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    mov     rax, QWORD [rbp - 16]    ; Load character from s2
    movzx   eax, BYTE [rax]          ; Zero-extend character to 32 bits (lower 8 bits of rax)

    cmp     dl, al                   ; Compare characters
    jge     .return_0                ; Jump to return_0 if s1 >= s2

    mov     eax, -1                  ; s1 < s2, set return value to -1
    jmp     .return                  ; Jump to return

.return_0:
    mov     eax, 0                   ; s1 and s2 are equal, set return value to 0

.return:
    pop     rbp                      ; Epilogue
    ret                              ; Return from the function
