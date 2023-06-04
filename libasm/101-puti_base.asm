section .text
extern asm_strlen
extern asm_putc
global asm_puti_base

asm_puti_base:
    push    rbp                     ; Function prologue
    mov     rbp, rsp                ;
    sub     rsp, 48                 ;
    mov     DWORD [rbp - 36], edi   ; Reserve space on the stack for 'n' (input parameter)
    mov     QWORD [rbp - 48], rsi   ; Reserve space on the stack for 'base'
    mov     DWORD [rbp - 4], 1      ; Reserve space on the stack for 'pow_of_bs = 1'
    mov     QWORD [rbp - 16], 0     ; Reserve space on the stack for 'i = 0'
    mov     QWORD [rbp - 24], 1     ; Reserve space on the stack for 'chr_cnt = 1'
    mov     rax, QWORD [rbp - 48]   ;
    mov     rdi, rax                ; Move 'base' into 'rdi' to act as a parameter to 'asm_strlen'
    call    asm_strlen              ; Call 'asm_strlen' to get the length of 'base'
    mov     DWORD [rbp - 28], eax   ; Reserve space on the stack for 'bs = asm_strlen(base)'
    cmp     DWORD [rbp - 28], 1     ; Is 'bs' less than 2?
    ja      .n_neg_test             ;
    mov     eax, 0           	    ; Returning 0
    jmp     .return           	    ;

.n_neg_test:                        ;
    cmp     DWORD [rbp - 36], 0     ; Is 'n' less than 0?
    jns     .n_pos                  ;
    mov     edi, 45                 ; '-' (ASCII value)
    call    asm_putc                ; Call 'asm_putc' to print the character
    add     QWORD [rbp - 16], 1     ; i++
    add     QWORD [rbp - 24], 1     ; chr_cnt++
    mov     eax, DWORD [rbp - 36]   ;
    neg     eax                     ; Negate 'n' using 2's complement
    mov     DWORD [rbp - 8], eax    ; Reserve space on the stack for 'temp = -n'
    jmp     .pow_of_bs_loop_test    ;

.n_pos:                             ;
    mov     eax, DWORD [rbp - 36]   ;
    mov     DWORD [rbp - 8], eax    ; Reserve space on the stack for 'temp = n'
    jmp     .pow_of_bs_loop_test    ;

.pow_of_bs_loop:                    ;
    mov     eax, DWORD [rbp - 4]    ;
    imul    eax, DWORD [rbp - 28]   ; Multiply 'pow_of_bs' by 'bs'
    mov     DWORD [rbp - 4], eax    ; Store the result in 'pow_of_bs'
    add     QWORD [rbp - 24], 1     ; chr_cnt++

.pow_of_bs_loop_test:        ;
    mov     eax, DWORD [rbp - 8]    ;
    mov     edx, 0                  ; Initialize the return register for division (edx)
    div     DWORD [rbp - 28]        ; Divide 'temp' by 'bs'
    cmp     eax, DWORD [rbp - 4]    ; Is the quotient greater than or equal to 'pow_of_bs'?
    jnb     .pow_of_bs_loop         ;
    jmp     .print_loop_test        ;

.print_loop:                        ;
    mov     eax, DWORD [rbp - 8]    ;
    mov     edx, 0                  ; Initialize the return register for division (edx)
    div     DWORD [rbp - 4]         ; Divide 'temp' by 'pow_of_bs'
    mov     edx, eax                ;
    mov     rax, QWORD [rbp - 48]   ;
    add     rax, rdx                ; Get the character at base[div result] (base + div result)
    movzx   eax, BYTE [rax]         ;
    movsx   eax, al                 ; Dereference (base + div result)
    mov     edi, eax                ; Move the character to 'edi' as a parameter for 'asm_putc'
    call    asm_putc                ; Call 'asm_putc' to print the character
    mov     eax, DWORD [rbp - 8]    ;
    mov     edx, 0                  ; Initialize the return register for division (edx)
    div     DWORD [rbp - 4]         ; Get the remainder (edx) as the new 'temp'
    mov     DWORD [rbp - 8], edx    ; Store the remainder in 'temp'
    mov     eax, DWORD [rbp - 4]    ;
    mov     edx, 0                  ; Initialize the return register for division (edx)
    div     DWORD [rbp - 28]        ; Divide 'pow_of_bs' by 'bs'
    mov     DWORD [rbp - 4], eax    ; Store the quotient (eax) as the new 'bs'
    add     QWORD [rbp - 16], 1     ; i++

.print_loop_test:                   ;
    mov     rax, QWORD [rbp - 16]   ;
    cmp     rax, QWORD [rbp - 24]   ; Is 'i' less than 'chr_cnt'?
    jb      .print_loop             ;
    mov     rax, QWORD [rbp - 24]   ;

.return:                            ;
    leave                           ; Restore the previous stack frame
    ret                             ; Return from the function
