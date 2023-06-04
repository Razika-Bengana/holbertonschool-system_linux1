section .text
global asm_strcasecmp

asm_strcasecmp:
	push rbp                  ; Prologue: Save the base pointer
	mov rbp, rsp              ; Set the base pointer
	mov qword [rbp - 24], rdi ; Store the pointer to the first string
	mov qword [rbp - 32], rsi ; Store the pointer to the second string
	mov dword [rbp - 4], 0    ; Initialize the comparison result

	jmp dif_s1_s2             ; Jump to start the comparison loop

t_1:	                          ;Code block to handle conversion of uppercase to lowercase
	mov rax, qword [rbp - 24] ; Move the pointer to the first string to rax
	movzx eax, byte [rax]     ; Load the first character and zero-extend to full register
	cmp al, 64                ; Compare the ASCII value with 64 ('@')
	jle false_t_1             ; Jump if the character is less than or equal to '@'
	mov rax, qword [rbp - 24] ; Move the pointer to the first string to rax
	movzx eax, byte [rax]     ; Load the first character and zero-extend to full register
	cmp al, 90                ; Compare the ASCII value with 90 ('Z')
	jg false_t_1              ; Jump if the character is greater than 'Z'
	mov rax, qword [rbp - 24] ; Move the pointer to the first string to rax
	movzx eax, byte [rax]     ; Load the first character and zero-extend to full register
	add eax, 32               ; Convert uppercase to lowercase
	jmp true_t_1              ; Jump to store the lowercase character

false_t_1:
	mov rax, qword [rbp - 24] ; Move the pointer to the first string to rax
	movzx eax, byte [rax]     ; Load the first character and zero-extend to full register

true_t_1:
	mov byte [rbp - 5], al    ; Store the lowercase character in a temporary variable

	mov rax, qword [rbp - 32] ; Move the pointer to the second string to rax
	movzx eax, byte [rax]     ; Load the second character and zero-extend to full register
	cmp al, 64                ; Compare the ASCII value with 64 ('@')
	jle false_t_2             ; Jump if the character is less than or equal to '@'
	mov rax, qword [rbp - 32] ; Move the pointer to the second string to rax
	movzx eax, byte [rax]     ; Load the second character and zero-extend to full register
	cmp al, 90                ; Compare the ASCII value with 90 ('Z')
	jg false_t_2              ; Jump if the character is greater than 'Z'
	mov rax, qword [rbp - 32] ; Move the pointer to the second string to rax
	movzx eax, byte [rax]     ; Load the second character and zero-extend to full register
	add eax, 32               ; Convert uppercase to lowercase
	jmp dif_search            ; Jump to continue the comparison

false_t_2:
	mov rax, qword [rbp - 32] ; Move the pointer to the second string to rax
	movzx eax, byte [rax]     ; Load the second character and zero-extend to full register

dif_search:
	mov byte [rbp - 6], al    ; Store the lowercase character of the second string

	movsx edx, byte [rbp - 5] ; Sign-extend the first character to full register
	movsx eax, byte [rbp - 6] ; Sign-extend the second character to full register
	sub edx, eax              ; Subtract the second character from the first character
	mov eax, edx              ; Move the result to eax

	mov dword [rbp - 4], eax  ; Store the comparison result

	add qword [rbp - 24], 1   ; Increment the pointer to the first string
	add qword [rbp - 32], 1   ; Increment the pointer to the second string

dif_s1_s2:
	mov rax, qword [rbp - 24] ; Move the pointer to the first string to rax
	movzx eax, byte [rax]     ; Load the character and zero-extend to full register
	test al, al               ; Test if the character is null (end of string)
	jne dif_test              ; Jump to perform the comparison if not null
	mov rax, qword [rbp - 32] ; Move the pointer to the second string to rax
	movzx eax, byte [rax]     ; Load the character and zero-extend to full register
	test al, al               ; Test if the character is null (end of string)
	je dif_ret                ; Jump to return if both strings are equal

dif_test:
	cmp dword [rbp - 4], 0    ; Compare the comparison result with 0
	je t_1                    ; Jump to handle the different case of the first character

dif_ret:
	mov eax, dword [rbp - 4]  ; Move the comparison result to eax
	pop rbp                   ; Epilogue: Restore the base pointer
	ret                       ; Return from the function
