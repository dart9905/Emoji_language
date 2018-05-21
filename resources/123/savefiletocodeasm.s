extern _printf
extern _scanf
section .data
Text:       dq      "%i",10,0
.len        equ     $ - Text
STR:        dq      0
.len        equ     $ - STR
array       dq      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
section .text
global _main
_main:
mov     r14,    Text
mov     r15,    array
sub     r15,    Text.len
sub     r15,    STR.len
mov     r13,    STR
sub     r13,    Text.len
jmp begin


;rbx
global PrintTen
PrintTen:
    mov     r8, rbx
    mov     rax,    '+'
    Push rax
    xor     rax,    rax
    mov     ecx,    10d            ;dl
    mov     rax,    r8       ; Get symbol

T_start:
    xor     rdx,    rdx
    div ecx                ;dl

    cmp eax, 0h            ; if end of num
    je T_end1            ; break

    Push rdx

    xor     edx,    edx
    jmp T_start

T_end1:
    add     rdx,    '0'
    mov     [rsi],  rdx

    mov rax, 0x2000004      ; System call write = 4
    mov rdi, 1              ; Write to standard out = 1
    mov rdx, 1              ; The size to write
    syscall                 ; Invoke the kernel

    Pop rdx
    cmp rdx, '+'            ; if(ah != '$')
    jne T_end1              ;   jump T_end1

    ret


l101:
pop r9
pop rbx
mov qword [r15+1], rbx
pop rbx
mov qword [r15+2], rbx
push r9

mov qword rax, [r15+1]
mov qword rbx, 1
sub rax, rbx
push rax
mov qword rax, [r15+2]
pop rbx
mul bx
push rax
pop r12
mov qword [r15+2], r12

mov qword rax, [r15+1]
mov qword rbx, 1
sub rax, rbx
push rax
pop r12
mov qword [r15+1], r12

mov qword rax, [r15+1]
mov qword rbx, 1
cmp rax, rbx

jbe l102
mov qword rbx, [r15+2]
push rbx
mov qword rbx, [r15+1]
push rbx
call l101
pop rbx
mov qword [r15+2], rbx
pop rbx
mov qword [r15+1], rbx
l102:

pop r9
mov qword rbx, [r15+1]
push rbx
mov qword rbx, [r15+2]
push rbx
push r9
ret

begin:
mov qword r12, 2
mov qword [r15+3], r12
mov qword [r15+4], r12

mov qword rbx, [r15+4]
push rbx
mov qword rbx, [r15+3]
push rbx
call l101
pop rbx
mov qword [r15+4], rbx
pop rbx
mov qword [r15+3], rbx
mov qword rbx, [r15+4]
call PrintTen

mov rax, 0x2000001      ; System call number for exit = 1
mov rdi, 0              ; Exit success = 0
syscall                 ; Invoke the kernel
