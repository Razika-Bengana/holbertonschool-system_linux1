section .text
global asm_puts
extern asm_strlen

asm_puts:
	push rbp                  ; Prologue: Save the base pointer
	mov rbp, rsp              ; Set the base pointer
	sub rsp, 32               ; Allocate space on the stack

	mov qword [rbp - 24], rdi ; Store the pointer to the string

	mov rax, qword [rbp - 24] ; Move the string pointer to rax
	mov rdi, rax              ; Set the first argument (rdi) to the string pointer
	mov eax, 0                ; Clear eax (lower 32 bits of rax) for the call
	call asm_strlen           ; Call the asm_strlen function to determine the string length
	mov dword [rbp - 4], eax  ; Store the string length

	mov edx, dword [rbp - 4]  ; Set the length of data to be output
	mov rax, qword [rbp - 24] ; Move the string pointer to rax
	mov rsi, rax              ; Set the second argument (rsi) to the string pointer
	mov edi, 1                ; Set the file descriptor (stdout)
	mov eax, 1                ; Set the system call number (sys_write)
	syscall                   ; Call the operating system to output the string

	cdqe                      ; Sign-extend eax to rax
	leave                     ; Epilogue: Restore the stack frame
	ret                       ; Return from the function
