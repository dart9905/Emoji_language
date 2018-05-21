extern _printf
extern _scanf
section .data
Text:       dq      "%i",0
.len        equ     $ - Text
STR:        dq      0
.len        equ     $ - STR
array       dq      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
section .text
global start
start:
mov     r14,    Text
mov     r15,    array
sub     r15,    Text.len
sub     r15,    STR.len
mov     r13,    STR
sub     r13,    Text.len
jmp begin
l101:
mov qword rbx, [r15+1]
pop rbx
mov qword rbx, [r15+2]
pop rbx
mov qword rax, [r15+1]
mov qword rbx, 1
sub rax, rbx
push rax
mov qword rax, [r15+2]
pop rbx
mul ebx
push rax
mov qword r12, [r15+2]
pop r12
mov qword rax, [r15+1]
mov qword rbx, 1
sub rax, rbx
push rax
mov qword r12, [r15+1]
pop r12
mov qword rax, [r15+1]
mov qword rbx, 1
cmp rax, rbx
jbe l102
mov qword rbx, [r15+2]
push rbx
mov qword rbx, [r15+1]
push rbx
call l101
mov qword rbx, [r15+2]
pop rbx
mov qword rbx, [r15+1]
pop rbx
l102:
mov qword rbx, [r15+1]
push rbx
mov qword rbx, [r15+2]
push rbx
ret

begin:
mov rsi, r13
mov rdi, r14
call _scanf
mov qword r11, [r13]
mov qword [r15+3], r11
mov qword r12, [r15+3]
push r12
mov qword r12, [r15+4]
pop r12
mov qword rbx, [r15+4]
push rbx
mov qword rbx, [r15+3]
push rbx
call l101
mov qword rbx, [r15+4]
pop rbx
mov qword rbx, [r15+3]
pop rbx
mov qword r11, [r15+4]
mov qword [r13], r11
mov rdi, r14
mov rsi, r13
call _printf

mov rax, 0x2000001      ; System call number for exit = 1
mov rdi, 0              ; Exit success = 0
syscall                 ; Invoke the kernel
