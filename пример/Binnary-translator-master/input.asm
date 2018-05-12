section .text
global _start
_start:	
	mov rbp, rsp
	sub rsp, 1024

	jmp .lol
	mov rax, 3
	mov rbx, 2
	mov rcx, buffer
	mov rdx, 10
	int 80h

	mov rdi, buffer
	xor rax, rax
	xor rbx, rbx	
	mov bl, byte [rdi]
	cmp bl, '-'
	jne .nxt
	
	inc rdi
	mov bl, byte [rdi]	

.nxt:	sub bl, 30h
	mov rcx, 10d
	mul rcx
	add rax, rbx
	
	inc rdi
	xor rbx, rbx
	mov bl, byte [rdi]
	cmp bl, 30
	jae .nxt

	mov bl, byte [buffer]
	cmp bl, '-'
	je .sign
	jmp .unsign

.sign:	mov rdx, -1
	mul rdx

.unsign:
jmp .lol
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	mov rbx, 1000000000d
	mov rdi, buffer
	mov rsi, numbers
	mov r8, 0
		
	mov rcx, 80000000h
	and rcx, rax
	cmp rcx, 0
	je .uns

	mov rcx, -1
	xor rdx, rdx
	mul rcx
	mov byte bl, '-'
	mov byte [rdi], bl
	inc rdi
	mov rcx, 1
	jmp .Nxt

.uns:	xor rcx, rcx
	
.Nxt:	mov rdx, 0
	div rbx
	cmp rax, r8
	je .zero
	mov r8, 11
	add rsi, rax
	push rbx	
	mov byte bl, [rsi]
	mov byte [rdi], bl
	pop rbx
	sub rsi, rax
	inc rdi
	inc rcx

.zero:	push rdx
	
	mov rax, rbx
	mov rbx, 10d
	mov rdx, 0
	div rbx
	mov rbx, rax
	
	pop rax
	cmp rbx, 0d
	jne .Nxt

	mov byte bl, 0ah
	mov byte [rdi], bl
	inc rcx
	
	mov rax, 1
	mov rdi, 1
	mov rsi, buffer
	mov rdx, rcx
	syscall
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
.add:	push 80
	push 70
	
	pop rbx
	pop rax
	add rax, rbx
	push rax
	
.sub:	push 80
	push 70
	
	pop rbx
	pop rax
	sub rax, rbx
	push rax

	jmp .div


.mul:	push 80
	push 70
	
	pop rbx
	pop rax
	push rdx	
	imul rbx
	pop rdx
	push rax


.div:	push 80
	push 10
		
	pop rbx
	pop rax
	push rdx	
	xor rdx, rdx
	idiv rbx
	pop rdx
	push rax

	jmp .lol
	pop rbx
	pop rax
	cmp rax, rbx
	ja .nxt
	
	pop rbx
	pop rax
	cmp rax, rbx
	jb .nxt
	
	pop rbx
	pop rax
	cmp rax, rbx
	jae .nxt
	
	pop rbx
	pop rax
	cmp rax, rbx
	jbe .nxt

	pop rbx
	pop rax
	cmp rax, rbx
	je .nxt

	pop rbx
	pop rax
	cmp rax, rbx
	jne .nxt
.lol:	
	;mov rax, [rbp - 100 * 8]
	;push rax
	push rbp
	sub rbp, 100*8
	mov rax, [rbp]
	pop rbp
	push rax	 
	
	pop rax
	push rbp
	sub rbp, 100 * 8
	mov [rbp], rax
	pop rbp

.regs:
	mov rax, rax
	mov ebx, 8
	mul ebx
	push rbp
	sub rbp, rax
	mov rax, [rbp]
	pop rbp
	push rax
.regsp:	
	mov rax, rax
	mov ebx, 8
	mul ebx
	pop rbx
	push rbp
	sub rbp, rax
	mov [rbp], rbx
	pop rbp

	call _ff 

	mov rax, 60
	xor rdi, rdi
	syscall

_ff:
	ret


section .data
buffer times 11 db 0h
numbers db "0123456789"
