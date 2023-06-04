section .text
global asm_memcpy

asm_memcpy:
	push rbp                    ; Prologue: Save the base pointer
	mov rbp, rsp                ; Set the base pointer

	mov qword [rbp - 40], rdi   ; Store the source address
	mov qword [rbp - 48], rsi   ; Store the destination address
	mov qword [rbp - 56], rdx   ; Store the length of data to be copied

	mov rax, qword [rbp - 40]   ; Copy source address to a temporary variable
	mov qword [rbp - 16], rax   ; Store the source address for future use
	mov rax, qword [rbp - 48]   ; Copy destination address to a temporary variable
	mov qword [rbp - 24], rax   ; Store the destination address for future use

	cmp qword [rbp - 16], 0     ; Check if source address is NULL
	je  mem_loc                 ; Jump to mem_loc if it is NULL

	cmp qword [rbp - 24], 0     ; Check if destination address is NULL
	jne loop_start              ; Jump to loop_start if it is not NULL

mem_loc:
	mov rax, qword [rbp - 40]   ; Return the source address
	jmp return_label

loop_start:
	mov qword [rbp - 8], 0      ; Initialize the loop counter to zero
	jmp loop_test_label

loop:
	mov rax, qword [rbp - 8]    ; Get the current loop counter
	mov rdx, qword [rbp - 16]   ; Get the source address
	add rdx, rax                ; Calculate the address to copy from
	mov rax, qword [rbp - 8]    ; Get the current loop counter
	mov rcx, qword [rbp - 24]   ; Get the destination address
	add rax, rcx                ; Calculate the address to copy to
	movzx eax, byte [rax]       ; Load a byte from the source address
	mov byte [rdx], al          ; Store the byte to the destination address
	add qword [rbp - 8], 1      ; Increment the loop counter

loop_test_label:
	mov rax, qword [rbp - 8]    ; Get the current loop counter
	cmp rax, qword [rbp - 56]   ; Compare it with the length of data
	jb loop                     ; If it is less than the length, continue the loop

	mov rax, qword [rbp - 40]   ; Return the source address

return_label:
	pop rbp                     ; Epilogue: Restore the base pointer
	ret                         ; Return from the function
