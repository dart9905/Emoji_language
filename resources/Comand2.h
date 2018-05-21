#define GOTO + 100


#define GOTO_WHILE \
    if (cell->prev != NULL)\
        if (strcmp(cell->prev->data, "while") == 0) {\
            stack->Push(stack, stack->Peek(stack) + 1);\
            fprintf(file, "l%i:\n", stack->Peek(stack) GOTO);\
        }\

#define READAXBX \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"mov qword rax, %s\n", cell->nextl->data);\
    } else \
        fprintf(file,"pop rax\n");\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"mov qword rbx, %s\n", cell->nextr->data);\
    } else \
        fprintf(file,"pop rbx\n");


#define DEF_ADD \
    READAXBX\
    fprintf(file, "add eax, ebx\npush rax\n");\
    return 0;


#define SUB_DEF \
    READAXBX\
    fprintf(file, "sub rax, rbx\npush rax\n");\
    return 0;


#define DIV_DEF \
    READAXBX\
    fprintf(file, "div ebx\npush rax\n");\
    return 0;


#define MUL_DEF \
    READAXBX\
    fprintf(file, "mul bx\npush rax\n");\
    return 0;


#define EQU_DEF \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"mov qword r12, %s\n", cell->nextl->data);\
        fprintf(file,"push r12\n");\
    }\
\
    if ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL)) {\
        fprintf(file,"pop r12\n");\
        fprintf(file,"mov qword %s, r12\n", cell->nextr->data);\
    }\
    return 0;


#define DEF_IF \
    fprintf(file, "l%i:\n", stack->Pop (stack) GOTO);\
    return 0;


#define MOR_DEF \
    GOTO_WHILE\
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "jbe l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define LES_DEF \
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "jae l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define EQUEQU_DEF \
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "jne l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define NOEQU_DEF \
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "je l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define LESEQU_DEF \
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "ja l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define MOREQU_DEF \
    READAXBX\
    fprintf(file, "cmp rax, rbx\n");\
    stack->Push(stack, stack->number + 1);\
    fprintf(file, "jb l%i\n", stack->Peek(stack) GOTO);\
    return 0;


#define DEF_WHI \
    fprintf(file, "call l%i\n", stack->Peek(stack) - 1 GOTO);\
    fprintf(file, "l%i:\n", stack->Pop(stack) GOTO);\
    stack->Pop(stack);\
    return 0;

//fprintf(file,"end\n");
#define DEF_END \
    fprintf(file,"\n");\
    fprintf(file,"mov rax, 0x2000001      ; System call number for exit = 1\n");\
    fprintf(file,"mov rdi, 0              ; Exit success = 0\n");\
    fprintf(file,"syscall                 ; Invoke the kernel\n");\
    return 0;


#define DEF_BEG \
fprintf(file,"begin:\n");\
    return 0;


#define DEF_REA \
if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
    fprintf(file,"mov rsi, r13\n");\
    fprintf(file,"mov rdi, r14\n");\
    fprintf(file,"xor rax, rax\n");\
    fprintf(file,"call _scanf\n");\
    fprintf(file,"mov qword r11, [r13]\n");\
    fprintf(file,"mov qword %s, r11\n", cell->nextl->data);\
}\
return 0;


#define DEF_PRI \
if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
    fprintf(file,"mov qword rbx, %s\n", cell->nextl->data);\
    fprintf(file,"call PrintTen\n");\
}\
return 0;


#define DEF_SQR \
    if ((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) {\
        fprintf(file,"push %s\n", cell->nextl->data);\
    }\
\
    fprintf(file, "sqrt\n");\
    return 0;






DEF_CMD( begin, DEF_BEG )
DEF_CMD( while, DEF_WHI )
DEF_CMD( if, DEF_IF )
DEF_CMD( end, DEF_END )
DEF_CMD( read, DEF_REA )
DEF_CMD( print, DEF_PRI )
DEF_CMD( sqrt, DEF_SQR )
DEF_CMD( +, DEF_ADD )
DEF_CMD( -, SUB_DEF )
DEF_CMD( /, DIV_DEF )
DEF_CMD( *, MUL_DEF )
DEF_CMD( =, EQU_DEF )
DEF_CMD( >, MOR_DEF)
DEF_CMD( <, LES_DEF)
DEF_CMD( ==, EQUEQU_DEF)
DEF_CMD( !=, NOEQU_DEF)
DEF_CMD( <=, LESEQU_DEF)
DEF_CMD( >=, MOREQU_DEF)
//DEF_CMD( ;, return 0;)






#undef DEF_SQR
#undef DEF_REA
#undef DEF_PRI
#undef DEF_END
#undef DEF_BEG
#undef GOTO
#undef GOTO_WHILE
#undef DEF_WHI
#undef DEF_IF
#undef DEF_ADD
#undef SUB_DEF
#undef DIV_DEF
#undef MUL_DEF
#undef EQU_DEF
#undef MOR_DEF
#undef LES_DEF
#undef EQUEQU_DEF
#undef LESEQU_DEF
#undef MOREQU_DEF
