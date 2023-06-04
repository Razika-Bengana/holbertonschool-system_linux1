section .text
global asm_strncasecmp

asm_strncasecmp:
    push rbp                              ; Save the base pointer
    mov rbp, rsp                          ; Set up the base pointer

    mov QWORD [rbp - 24], rdi             ; Store s1 parameter on the stack
    mov QWORD [rbp - 32], rsi             ; Store s2 parameter on the stack
    mov QWORD [rbp - 40], rdx             ; Store n parameter on the stack
    mov QWORD [rbp - 8], 0                ; Initialize i (counter) to 0
    mov DWORD [rbp - 12], 0               ; Initialize diff (and c1, c2) to 0

    jmp compare_s1_s2                     ; Jump to start comparing s1 and s2

compare_t1:
    mov rax, QWORD [rbp - 24]
    movzx eax, BYTE [rax]
    cmp al, 64
    jle false_t1
    mov rax, QWORD [rbp - 24]
    movzx eax, BYTE [rax]
    cmp al, 90
    jg false_t1
    mov rax, QWORD [rbp - 24]
    movzx eax, BYTE [rax]
    add eax, 32
    jmp true_t1

false_t1:
    mov rax, QWORD [rbp - 24]
    movzx eax, BYTE [rax]

true_t1:
    mov BYTE [rbp - 13], al               ; Store c1 (s1[i] + ' ') in a temporary variable

    mov rax, QWORD [rbp - 32]
    movzx eax, BYTE [rax]
    cmp al, 64
    jle false_t2
    mov rax, QWORD [rbp - 32]
    movzx eax, BYTE [rax]
    cmp al, 90
    jg false_t2
    mov rax, QWORD [rbp - 32]
    movzx eax, BYTE [rax]
    add eax, 32
    jmp compare_chars

false_t2:
    mov rax, QWORD [rbp - 32]
    movzx eax, BYTE [rax]

compare_chars:
    mov BYTE [rbp - 14], al               ; Store c2 (s2[i] + ' ') in a temporary variable
    movsx edx, BYTE [rbp - 13]            ; Sign-extend c1
    movsx eax, BYTE [rbp - 14]            ; Sign-extend c2
    sub edx, eax                          ; Calculate diff (c1 - c2)
    mov eax, edx                          ; Store the result in eax
    mov DWORD [rbp - 12], eax             ; Store diff in a temporary variable

    add QWORD [rbp - 24], 1               ; Increment s1 pointer
    add QWORD [rbp - 32], 1               ; Increment s2 pointer
    add QWORD [rbp - 8], 1                ; Increment i

compare_s1_s2:
    mov rax, QWORD [rbp - 24]
    movzx eax, BYTE [rax]
    test al, al
    jne compare_test                      ; If s1[i] is not null, proceed to compare
    mov rax, QWORD [rbp - 32]
    movzx eax, BYTE [rax]
    test al, al
    je compare_ret                        ; If s2[i] is null, return

compare_test:
    cmp DWORD [rbp - 12], 0               ; Compare diff to zero
    jne compare_ret                       ; If diff is not zero, return
    mov rax, QWORD [rbp - 8]
    cmp rax, QWORD [rbp - 40]
    jb compare_t1                         ; If i < n, continue comparing

compare_ret:
    mov eax, DWORD [rbp - 12]             ; Move diff to eax (return value)
    pop rbp                               ; Restore the base pointer
    ret                                   ; Return
