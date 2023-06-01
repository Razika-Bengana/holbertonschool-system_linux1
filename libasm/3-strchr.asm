section .text
global asm_strchr

asm_strchr:
	push    rbp				; Prologue
	mov     rbp, rsp

	mov     QWORD [rbp - 24], rdi		; Reserve space on the stack for s
	mov     DWORD [rbp - 28], esi		; Reserve space on the stack for c

	mov     rax, QWORD [rbp - 24]		; Cast s to rax
	mov     QWORD [rbp - 8], rax		; Reserve space on the stack for temp

	jmp     .temp_loop_test			; Jump to the loop test

.temp_loop:					; Loop to search for c in s
	mov     rax, QWORD [rbp - 8]		; Load temp into rax
	movzx   eax, BYTE [rax]			; Load the byte at *temp into eax
	movsx   eax, al				; Sign-extend the byte value to a DWORD

	cmp     eax, DWORD [rbp - 28]		; Compare *temp with c
	jne     .inc_temp			; If *temp != c, increment temp

	mov     rax, QWORD [rbp - 8]		; If *temp == c, load temp into rax
	jmp     .return				; Jump to the return statement

.inc_temp:					; Increment temp and continue the loop
	add     QWORD [rbp - 8], 1		; Increment temp by 1

.temp_loop_test:				; Test condition for the loop
	mov     rax, QWORD [rbp - 8]		; Load temp into rax
	movzx   eax, BYTE [rax]			; Load the byte at *temp into eax
	test    al, al				; Test if *temp == '\0'
	jne     .temp_loop			; If *temp != '\0', continue the loop

	cmp     DWORD [rbp - 28], 0		; Compare c with 0
	jne     .return_null			; If c != 0, return null pointer

	mov     rax, QWORD [rbp - 8]		; If c == 0, load temp into rax
	jmp     .return				; Jump to the return statement

.return_null:					; Return null pointer
	mov     eax, 0				; Set eax to 0

.return:					; Return statement
	pop     rbp				; Epilogue
	ret					; Return from the function
