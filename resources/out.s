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