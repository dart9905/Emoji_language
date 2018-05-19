#include "enums.h"

#define DB(value)\
	{size_t temp = value;\
	memcpy (this -> output_current, &temp, 1);\
	this -> output_current += 1;}

#define DW(value)\
	{size_t temp = value;\
	memcpy (this -> output_current, &temp, 2);\
	this -> output_current += 2;}

#define DD(value)\
	{size_t temp = value;\
	memcpy (this -> output_current, &temp, 4);\
	this -> output_current += 4;}

#define DQ(value)\
	{size_t temp = value;\
	memcpy (this -> output_current, &temp, 8);\
	this -> output_current += 8;}

#define GETINT this -> get_int ()

//11
//pop rbx
//pop rax
//cmp rax, rbx
//ja <label>
#define JUMP(number)\
	{\
		DB (0x5b)\
		DB (0x58)\
		DB (0x48) DB (0x39) DB (0xd8)\
		DB (0x0f) DB (0x82 + number) DD (GETINT - (size_t)( this -> output_current) + (size_t) (this -> output_buffer) - 4)\
	}

TRAN_CMD(END, {								//17
		DW (0x8148) DB (0xc5) DD (0x400)    
		DB (0xb8)   DD (0x3c)					//mov rax, 60
		DW (0x3148) DB (0xff)					//xor rdi, rdi
		DW (0x050f) 						//syscall 

		})

TRAN_CMD(OUT, { 							//194
		DB (0x58)						//pop rax
		
		DB (0x53)						//push rbx
		DB (0x51)						//push rcx
		DB (0x52)						//push rdx
		
		DB (0xbb) DD (0x3b9aca00)				//mov rbx, 1000000000d
		DB (0x48) DB (0xbf) DQ (0x6000c2)			//mov rdi, buffer
		DB (0x48) DB (0xbe) DQ (0x6000b2)			//mov rsi, numbers
		DB (0x41) DB (0xb8) DD (0x00)				//mov r8, 0
		DB (0xb9) DD (0x80000000)//40 				//mov rcx, 80000000h
		DB (0x48) DB (0x21) DB (0xc1)				//and rcx, rax
		DW (0x8348) DB (0xf9) DB (0x00)				//cmp rcx, 0
		DB (0x74) DB (0x1b)					//je     400176 <_start.uns>
		DB (0x48) DW (0xc1c7) DD (0xffffffff)			//mov rcx, -1
		DW (0x3148) DB (0xd2)					//xor rdx, rdx
		DW (0xf748) DB (0xe1)					//mul rcx
		DB (0xb3) DB (0x2d)					//mov byte bl, '-'
		DB (0x88) DB (0x1f)					//mov byte [rdi], bl
		DW (0xff48) DB (0xc7)					//inc rdi
		DB (0xb9) DD (0x1)					//mov rcx, 1
		DB (0xeb) DB (0x03)					//jmp    400179 

		DW (0x3148) DB (0xc9)					//xor rcx, rcx

		DB (0xba) DD (0x00)					//mov rdx, 0
		DW (0xf748) DB (0xf3)					//div rbx
		DB (0x4c) DB (0x39) DB (0xc0)				//cmp rax, r8
		DB (0x74) DB (0x18)					//je     40019e <_start.zero>
		DB (0x41) DB (0xb8) DD (0xb)				//mov r8, 11
		DB (0x48) DB (0x01) DB (0xc6)				//add rsi, rax
		DB (0x53)						//push rbx
		DB (0x8a) DB (0x1e)					//mov byte bl, [rsi]
		DB (0x88) DB (0x1f)					//mov byte [rdi], bl
		DB (0x5b)						//pop rbx
		DW (0x2948) DB (0xc6)					//sub rsi, rax
		DW (0xff48) DB (0xc7)					//inc rdi
		DW (0xff48) DB (0xc1)					//inc rcx

		DB (0x52)						//push rdx
		DW (0x8948) DB (0xd8)					//mov rax, rbx
		DB (0xbb) DD (0xa)					//mov rbx, 10d
		DB (0xba) DD (0x00)					//mov rdx, 0
		DW (0xf748) DB (0xf3)					//div rbx
		DW (0x8948) DB (0xc3)					//mov rbx, rax
		DB (0x58)						//pop rax
		DW (0x8348) DB (0xfb) DB (0x00)				//cmp rbx, 0d
		DB (0x75) DB (0xc0)					//jne    400179 <_start.Nxt>
		DW (0x8349) DW (0xf8)					//cmp r8, 0
		DB (0x75) DB (0x0a)					//jne .prt
		DB (0xb3) DB (0x30)					//mov byte bl, '0'
		DB (0x88) DB (0x1f)					//mov byte [rdi], bl
		DW (0xff48) DB (0xc7)					//inc rdi
		DW (0xff48) DB (0xc1)					//inc rcx
		
		DB (0xb3) DB (0xa)					//mov byte bl, 0ah
		DB (0x88) DB (0x1f)					//mov byte [rdi], bl
		DW (0xff48) DB (0xc1)					//inc rcx

		DB (0xb8) DD (0x1)					//mov rax, 1
		DB (0xbf) DD (0x1)					//mov rdi, 1
		DW (0xbe48) DQ (0x6000c2)				//mov rsi, buffer
		DW (0x8948) DB (0xca)					//mov rdx, rcx
		DW (0x050f)						//syscall

		DB (0x5a)						//push rdx
		DB (0x59)						//push rcx
		DB (0x5b)						//push rbx
		})

TRAN_CMD (PUSH, {
		int mode = GETINT;

		switch (mode)
		{
			case VAL:					//5
				DB (0x68) DD (GETINT)			//push <int>
		
				break;
	
			case REG:					//1
				DB (0x50 + GETINT)			//push <reg>

				break;	

			case RAM:					//14
				DB (0x55)				//push rbp
				DW (0x8148) DB (0xed) DD (GETINT * 8)	//sub rbp, <int>*8
				DD (0x458b48)				//mov rax, [rbp]
				DB (0x5d)				//pop rbp
				DB (0x50)				//push rax
	
				break;	
			
			case REGRAM:					//21
				DW (0x8948) DB (0xc0 + GETINT)		//mov rax, <reg>
				DB (0xba) DD (0x8)			//mov edx, 8
				DW (0xf748) DB (0xe2)			//mul edx
				DB (0x55)				//push rbp
				DW (0x2948) DB (0xc5)			//sub rbp, rax
				DD (0x458b48)				//mov rax, [rbp]
				DB (0x5d)				//pop rbp
				DB (0x50)				//push rax

				break;
		}
		})

TRAN_CMD (POP, {
		int mode = GETINT;

		switch (mode)
		{
			case REG:					//1
				DB (0x58 + GETINT)			//pop <reg>

				break;
			
			case RAM:					//14
				DB (0x58)				//pop rax
				DB (0x55)				//push rbp
				DW (0x8148) DB (0xed) DD (GETINT * 8)	//sub rbp, <int> * 8
				DD (0x458948)				//mov [rbp], rax
				DB (0x5d)				//pop rbp

				break;

			case REGRAM:					//20
				DW (0x8948) DB (0xc0 + GETINT)		//mov rax, <reg>
				DB (0xbb) DD (0x8)			//mov ebx, 8
				DB (0xf7) DB (0xe3)			//mul ebx	
				DB (0x5b)				//pop rbx
				DB (0x55)				//push rbp
				DW (0x2948) DB (0xc5)			//sub rbp, rax
				DD (0x5d8948)				//mov [rbp], rbx
				DB (0x5d)				//pop rbp

				break;
				
		}
		})

TRAN_CMD (IN, {								//113
		DB (0x53)						//push rbx
		DB (0x51)						//push rcx
		DB (0x52)						//push rdx

		DB (0xb8) DD (0x3)					//mov rax, 3
		DB (0xbb) DD (0x2)					//mov rbx, 2
		DB (0x48) DB (0xb9) DQ (0x6000c2)			//mov rcx, buffer
		DB (0xba) DD (0xa)					//mov rdx, 10
		DW (0x80cd)						//int 80h
		DB (0x48) DB (0xbf) DQ (0x6000c2)			//mov rdi, buffer
		DW (0x3148) DB (0xc0)					//xor rax, rax
		DW (0x3148) DB (0xdb)					//xor rbx, rbx
		DB (0x8a) DB (0x1f)					//mov bl, byte [rdi]
		DB (0x80) DB (0xfb) DB (0x2d)				//cmp bl, '-'
		DB (0x75) DB (0x05)					//jne    4000f6 <_start.nxt>
		DW (0xff48) DB (0xc7)					//inc rdi
		DB (0x8a) DB (0x1f)					//mov bl, byte [rdi]

		DB (0x80) DB (0xeb) DB (0x30)				//sub bl, 30h
		DB (0xb9) DD (0xa)					//mov rcx, 10d
		DW (0xf748) DB (0xe1)					//mul rcx
		DW (0x0148) DB (0xd8)					//add rax, rbx
		DW (0xff48) DB (0xc7)					//inc rdi
		DW (0x3148) DB (0xdb)					//xor rbx, rbx
		DB (0x8a) DB (0x1f)					//mov bl, byte [rdi]
		DB (0x80) DB (0xfb) DB (0x1e)				//cmp bl, 30
		DB (0x73) DB (0xe5)					//jae    4000f6 <_start.nxt>
		DW (0x1c8a) DB (0x25) DD (0x6000c2)			//mov bl, byte [buffer]
		DB (0x80) DB (0xfb) DB (0x2d)				//cmp bl, '-'
		DB (0x74) DB (0x02)					//je     40011f <_start.sign>
		DB (0xeb) DB (0x0a)					//jmp    400129 <_start.unsign>

		DB (0x48) DW (0xc2c7) DD (0xffffffff)			//mov rdx, -1
		DB (0x48) DW (0xe2f7)					//mul rdx

		DB (0x5a)						//pop rdx
		DB (0x59)						//pop rcx
		DB (0x5b)						//pop rbx

		DB (0x50)						//push rax
		})

TRAN_CMD (ADD, {							//6
		DB (0x5b)						//pop rbx
		DB (0x58)						//pop rax
		DW (0x0148) DB (0xd8)					//add rax, rbx
		DB (0x50)						//push rax
		})

TRAN_CMD (SUB, {							//6
		DB (0x5b)						//pop rbx
		DB (0x58)						//pop rax
		DW (0x2948) DB (0xd8)					//sub rax, rbx
		DB (0x50)						//push rax
		})

TRAN_CMD (MUL, {							//8
		DB (0x5b)						//pop rbx
		DB (0x58)						//pop rax
		DB (0x52)						//push rdx
		DW (0xf748) DB (0xeb)					//imul rbx
		DB (0x5a)						//pop rdx
		DB (0x50)						//push rax
		})

TRAN_CMD (DIV, {							//39
		DB (0x5b)						//pop rbx
		DB (0x58)						//pop rax
		DB (0x52)						//push rdx
		DW (0x3148) DB (0xd2)					//xor rdx, rdx
		DW (0x8348) DB (0xf8) DB (0x00)				//cmp rax, 0
		DB (0x7d) DB (0x16)					//jge .znak
		DB (0xb9) DD (0x00)					//mov rcx, 0
		DW (0x2948) DB (0xc1)					//sub rcx, rax
		DW (0x8948) DB (0xc8)					//mov rax, rcx
		DB (0xb9) DD (0x00)					//mov rcx, 0
		DW (0x2948) DB (0xd9)					//sub rcx, rbx
		DW (0x8948) DB (0xcb)					//mov rbx, rcx
		DW (0xf748) DB (0xfb)					//idiv rbx
		DB (0x5a)						//pop rdx
		DB (0x50)						//push rax
		})

TRAN_CMD (JMP, DB (0xe9) DD (GETINT - (size_t)( this -> output_current) + (size_t) (this -> output_buffer) - 4))							//jmp    40024e <_start.lol>

TRAN_CMD (JA , JUMP (0xd))
TRAN_CMD (JB , JUMP (0xa))
TRAN_CMD (JE , JUMP (0x2))
TRAN_CMD (JAE, JUMP (0xb))
TRAN_CMD (JBE, JUMP (0xc))
TRAN_CMD (JNE, JUMP (0x3))

TRAN_CMD (CALL, DB (0xe8) DD (GETINT - (size_t)( this -> output_current) + (size_t) (this -> output_buffer) - 4))							//callq  4002a1 <_ff>

TRAN_CMD (REV, DB  (0xc3))//1						//retq

TRAN_CMD (SQRT, {							//8
		DW (0x2cdf) DB (0x24)					//fild qword [rsp]
		DW (0xfad9)						//fsqrt
		DW (0x3cdf) DB (0x24)					//fistp qword [rsp]
		})
