section .text
global asm_putc

asm_putc:
	push rbp                 ; Prologue: Save the base pointer
	mov rbp, rsp             ; Set the base pointer
	sub rsp, 16              ; Allocate space on the stack

	mov dword [rbp - 4], edi ; Store the character to be output

	lea rax, [rbp - 4]       ; Calculate the address of the character
	mov edx, 1               ; Set the length of data to be output
	mov rsi, rax             ; Set the source address
	mov edi, 1               ; Set the file descriptor (stdout)
	mov eax, 1               ; Set the system call number (sys_write)
	syscall                  ; Call the operating system to output the character

	leave                    ; Epilogue: Restore the stack frame
	ret                      ; Return from the function
