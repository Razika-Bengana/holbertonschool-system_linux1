section	.text
extern asm_strlen
extern asm_putc
global asm_puti

asm_puti:
    push rbp
    mov rbp, rsp
    sub rsp, 48
    mov DWORD [rbp - 36], edi      ; Store the input parameter in [rbp - 36]
    mov DWORD [rbp - 4], 1         ; Initialize a counter at [rbp - 4]
    mov QWORD [rbp - 16], 0        ; Initialize a variable for quotient at [rbp - 16]
    mov QWORD [rbp - 24], 1        ; Initialize a variable for remainder at [rbp - 24]
    cmp DWORD [rbp - 36], 0        ; Compare the input parameter with 0
    jns ntt_c                      ; Jump to 'ntt_c' if the input is not negative
    mov edi, 45                    ; If negative, set the ASCII value of '-' character
    call asm_putc                  ; Call the 'asm_putc' function to print the character
    add QWORD [rbp - 16], 1        ; Increment the quotient by 1
    add QWORD [rbp - 24], 1        ; Increment the remainder by 1
    mov eax, DWORD [rbp - 36]      ; Move the input parameter to eax
    neg eax                        ; Negate the value in eax (convert it to positive)
    mov DWORD [rbp - 8], eax       ; Store the negated value in [rbp - 8]
    jmp mulx10_test                ; Jump to 'mulx10_test' to start the multiplication by 10

ntt_c:
    mov eax, DWORD [rbp - 36]      ; Move the input parameter to eax
    mov DWORD [rbp - 8], eax       ; Store the value in [rbp - 8]
    jmp mulx10_test                ; Jump to 'mulx10_test' to start the multiplication by 10

mulx10:
    mov eax, DWORD [rbp - 4]       ; Move the counter value to eax
    imul eax, 10                   ; Multiply eax by 10
    mov DWORD [rbp - 4], eax       ; Store the multiplied value back in [rbp - 4]
    add QWORD [rbp - 24], 1        ; Increment the remainder by 1

mulx10_test:
    mov eax, DWORD [rbp - 8]       ; Move the value to eax
    mov edx, 0                     ; Clear the edx register
    mov rcx, 10                    ; Move 10 to rcx
    div rcx                        ; Divide eax by 10, quotient in eax, remainder in edx
    cmp eax, DWORD [rbp - 4]       ; Compare the quotient with the counter value
    jnb mulx10                     ; Jump to 'mulx10' if the quotient is not less than the counter
    jmp prnt_test                  ; Jump to 'prnt_test' to start printing the digits

prnt:
    mov eax, DWORD [rbp - 8]       ; Move the value to eax
    mov edx, 0                     ; Clear the edx register
    div DWORD [rbp - 4]            ; Divide eax by the counter value, quotient in eax, remainder in edx
    add eax, 48                    ; Add 48 to eax to convert it to ASCII character value
    mov edi, eax                   ; Move the ASCII value to edi (parameter for asm_putc)
    call asm_putc                  ; Call the 'asm_putc' function to print the character
    mov eax, DWORD [rbp - 8]       ; Move the value to eax
    mov edx, 0                     ; Clear the edx register
    div DWORD [rbp - 4]            ; Divide eax by the counter value, quotient in eax, remainder in edx
    mov DWORD [rbp - 8], edx       ; Store the remainder back in [rbp - 8]
    mov eax, DWORD [rbp - 4]       ; Move the counter value to eax
    mov edx, 0                     ; Clear the edx register
    mov rcx, 10                    ; Move 10 to rcx
    div rcx                        ; Divide eax by 10, quotient in eax, remainder in edx
    mov DWORD [rbp - 4], eax       ; Store the quotient back in [rbp - 4]
    add QWORD [rbp - 16], 1        ; Increment the quotient by 1

prnt_test:
    mov rax, QWORD [rbp - 16]      ; Move the quotient value to rax
    cmp rax, QWORD [rbp - 24]      ; Compare the quotient with the remainder
    jb prnt                        ; Jump to 'prnt' if the quotient is less than the remainder
    mov rax, QWORD [rbp - 24]      ; Move the remainder value to rax
    leave                          ; Restore the previous stack frame
    ret                            ; Return from the function
