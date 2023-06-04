section .text
global asm_strstr

asm_strstr:
    push    rbp                         ; Prologue
    mov     rbp, rsp                    ;

    mov     QWORD [rbp - 40], rdi       ; Reserve space on stack for haystack
    mov     QWORD [rbp - 48], rsi       ; Reserve space on stack for needle

    mov     rax, QWORD [rbp - 40]       ; Cast haystack
    mov     QWORD [rbp - 8], rax        ; Reserve space on stack for hs
    mov     rax, QWORD [rbp - 48]       ; Cast needle
    mov     QWORD [rbp - 24], rax       ; Reserve space on stack for ndl

    mov     QWORD [rbp - 16], 0         ; Reserve space on stack for temp == NULL

    mov     rax, QWORD [rbp - 24]       ; Load needle character
    movzx   eax, BYTE [rax]             ; Zero-extend to full register
    test    al, al                      ; *hs == '\0'?
    jne     .haystack_loop_test         ; If not null, continue with haystack loop
    jmp     .return_hs                  ; Return haystack pointer

.setup_temp_loop:
    mov     rax, QWORD [rbp - 24]       ; Load needle pointer to temp
    mov     QWORD [rbp - 16], rax       ; temp = ndl
    jmp     .temp_loop_test             ; Jump to check temp

.temp_loop:
    mov     rax, QWORD [rbp - 16]       ; Load temp character
    movzx   edx, BYTE [rax]             ; Zero-extend to full register, dereference temp to edx
    mov     rcx, QWORD [rbp - 16]       ; Store temp pointer to rcx
    mov     rax, QWORD [rbp - 24]       ; Load needle pointer
    sub     rcx, rax                    ; Calculate temp - ndl
    mov     rax, rcx                    ; Move result to rax
    mov     rcx, rax                    ; Store temp - ndl in rcx
    mov     rax, QWORD [rbp - 8]        ; Load haystack pointer
    add     rax, rcx                    ; Calculate hs + (temp - ndl)
    movzx   eax, BYTE [rax]             ; Dereference result
    cmp     dl, al                      ; Compare result with *temp
    je      .increment_temp             ; If equal, increment temp
    jmp     .temp_test_after_loop       ; Jump to check temp loop termination

.increment_temp:
    add     QWORD [rbp - 16], 1         ; Increment temp

.temp_loop_test:
    mov     rax, QWORD [rbp - 16]       ; Load temp character
    movzx   eax, BYTE [rax]             ; Zero-extend to full register
    test    al, al                      ; *temp == '\0'?
    jne     .temp_loop                  ; If not null, continue temp loop

.temp_test_after_loop:
    mov     rax, QWORD [rbp - 16]       ; Load temp character
    movzx   eax, BYTE [rax]             ; Zero-extend to full register
    test    al, al                      ; *temp == '\0'?
    jne     .increment_haystack         ; If not null, increment haystack

.return_hs:
    mov     rax, QWORD [rbp - 8]        ; Return hs
    jmp     .return                     ; Jump to return

.increment_haystack:
    add     QWORD [rbp - 8], 1          ; Increment haystack

.haystack_loop_test:
    mov     rax, QWORD [rbp - 8]        ; Load haystack character
    movzx   eax, BYTE [rax]             ; Zero-extend to full register
    test    al, al                      ; *hs == '\0'?
    jne     .setup_temp_loop            ; If not null, continue with temp setup

.return_null:
    mov     eax, 0                      ; Return NULL

.return:
    pop     rbp                         ; Epilogue
    ret                                 ; Return from function
