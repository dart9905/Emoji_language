#include "enums.h"

#define DB(value)\
	{size_t temp = value;\
	memcpy (_output_current, &temp, 1);\
	_output_current = (char*)_output_current + 1;}

#define DW(value)\
	{size_t temp = value;\
	memcpy (_output_current, &temp, 2);\
	_output_current = ((char*)_output_current) + 2;}

#define DD(value)\
	{size_t temp = value;\
	memcpy (_output_current, &temp, 4);\
	_output_current = ((char*)_output_current) + 4;}

#define DQ(value)\
	{size_t temp = value;\
	memcpy (_output_current, &temp, 8);\
	_output_current = (char*)_output_current + 8;}

#define GETINT get_int ()

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
		DB (0x0f) DB (0x82 + number) DD (GETINT - (size_t)(_output_current) + (size_t) (_output_buffer) - 4)\
	}

TRAN_CMD(END, {								//17
		//DW (0x8148) DB (0xc5) DD (0x400)    
		DB (0xb8)   DD(0x02000001)				        //mov rax, 0x2000001
		DW (0x3148) DB (0xff)					        //xor rdi, rdi
		DW (0x050f) 						            //syscall

		})

TRAN_CMD(OUT, {
        DB (0x5e)                                       //pop rsi
        DB (0xb8) DD (0x0000002b)                       //mov rax, '+'
        DB (0x50)                                       //push rax
        DB(0x48)  DW(0xC031)                            //xor rax, rax
        DW(0x0AB9) DW(0x0000) DB(0x00)                  //mov ecx, 10d  ;dl
        DW(0x8948) DB(0xF0)                             //mov rax, rsi  ;Get symbol
        DW(0x3148) DB(0xD2)                             //xor rdx, rdx
        DW(0xF1F7)                                      //div ecx       ;dl
        DW(0xF883) DB(0x00)                             //cmp eax, 0h   ; if end of num
        DW(0x0574)                                      //je T_end1     ; break
        DB(0x52)                                        //Push rdx
        DW(0xD231)                                      //xor edx, edx
        DW(0xF1EB)                                      //jmp T_start
        DW(0x8348) DW(0x30C2)                           //add rdx, '0'
        DW(0xBE48) DW(0x2000) DD(0x00000000) DW(0x0000) //mov rsi, Text
        DW(0x8948) DB(0x16)                             //mov [rsi], rdx
        DW(0x5341)                                      //Push r11
        DW(0x04B8) DW(0x0000) DB(0x02)                  //mov rax, 0x2000004      ; System call write = 4
        DW(0x01BF) DW(0x0000) DB(0x00)                  //mov rdi, 1              ; Write to standard out = 1
        DW(0x01BA) DW(0x0000) DB(0x00)                  //mov rdx, 1              ; The size to write
        DW(0x050F)                                      //syscall                 ; Invoke the kernel
        DW(0x5B41)                                      //Pop r11
        DB(0x5A)                                        //Pop rdx
        DW(0x8348) DW(0x2BFA)                           //cmp rdx, '+'            ; if(ah != '$')
        DW(0xD375)                                      //jne T_end1              ;   jump T_end1
		})

TRAN_CMD (PUSH, {
		int mode = GETINT;

		switch (mode)
		{
			case VAL:					//5
				DB (0x68) DD (GETINT)			        //push <int>
		
				break;
	
			case REG:					//1
				DB (0x50 + GETINT)			            //push <reg>

				break;	

			case RAM:					//14
				DB (0x55)				                //push rbp
				DW (0x8148) DB (0xed) DD (GETINT * 8)	//sub rbp, <int>*8
				DD (0x458b48)				            //mov rax, [rbp]
				DB (0x5d)				                //pop rbp
				DB (0x50)				                //push rax
	
				break;	
			/*
			case REGRAM:					//21
				DW (0x8948) DB (0xc0 + GETINT)		    //mov rax, <reg>
				DB (0xba) DD (0x8)			            //mov edx, 8
				DW (0xf748) DB (0xe2)			        //mul edx
				DB (0x55)				                //push rbp
				DW (0x2948) DB (0xc5)			        //sub rbp, rax
				DD (0x458b48)				            //mov rax, [rbp]
				DB (0x5d)				                //pop rbp
				DB (0x50)				                //push rax
            */
				break;
		}
		})

TRAN_CMD (POP, {
		int mode = GETINT;

		switch (mode)
		{
			case REG:					//1
				DB (0x58 + GETINT)			            //pop <reg>

				break;
			
			case RAM:					//14
				DB (0x58)				                //pop rax
				DB (0x55)				                //push rbp
				DW (0x8148) DB (0xed) DD (GETINT * 8)	//sub rbp, <int> * 8
				DD (0x458948)				            //mov [rbp], rax
				DB (0x5d)				                //pop rbp

				break;

			case REGRAM:					//20
				DW (0x8948) DB (0xc0 + GETINT)		    //mov rax, <reg>
				DB (0xbb) DD (0x8)			            //mov ebx, 8
				DB (0xf7) DB (0xe3)			            //mul ebx
				DB (0x5b)				                //pop rbx
				DB (0x55)				                //push rbp
				DW (0x2948) DB (0xc5)			        //sub rbp, rax
				DD (0x5d8948)				            //mov [rbp], rbx
				DB (0x5d)				                //pop rbp

				break;
				
		}
		})
/*
TRAN_CMD (IN, {								//113
		DB (0x53)						                //push rbx
		DB (0x51)						                //push rcx
		DB (0x52)						                //push rdx
 

		DB (0x5a)						                //pop rdx
		DB (0x59)						                //pop rcx
		DB (0x5b)						                //pop rbx

		DB (0x50)						                //push rax
		})
 */

TRAN_CMD (ADD, {							//6
		DB (0x5b)						                //pop rbx
		DB (0x58)						                //pop rax
		DW (0x0148) DB (0xd8)					        //add rax, rbx
		DB (0x50)						                //push rax
		})

TRAN_CMD (SUB, {							//6
		DB (0x5b)						                //pop rbx
		DB (0x58)						                //pop rax
		DW (0x2948) DB (0xd8)			        		//sub rax, rbx
		DB (0x50)						                //push rax
		})

TRAN_CMD (MUL, {							//8
		DB (0x5b)						                //pop rbx
		DB (0x58)						                //pop rax
		DB (0x52)						                //push rdx
		DW (0xf748) DB (0xeb)					        //imul rbx
		DB (0x5a)						                //pop rdx
		DB (0x50)						                //push rax
		})

TRAN_CMD (DIV, {							//39
		DB (0x5b)						                //pop rbx
		DB (0x58)						                //pop rax
		DB (0x52)						                //push rdx
		DW (0x3148) DB (0xd2)					        //xor rdx, rdx
		DW (0x8348) DB (0xf8) DB (0x00)			    	//cmp rax, 0
		DB (0x7d) DB (0x16)					            //jge .znak
		DB (0xb9) DD (0x00)					            //mov rcx, 0
		DW (0x2948) DB (0xc1)					        //sub rcx, rax
		DW (0x8948) DB (0xc8)					        //mov rax, rcx
		DB (0xb9) DD (0x00)					            //mov rcx, 0
		DW (0x2948) DB (0xd9)					        //sub rcx, rbx
		DW (0x8948) DB (0xcb)					        //mov rbx, rcx
		DW (0xf748) DB (0xfb)					        //idiv rbx
		DB (0x5a)						                //pop rdx
		DB (0x50)						                //push rax
		})

TRAN_CMD (JMP, DB (0xe9) DD (GETINT - (size_t)(_output_current) + (size_t) (_output_buffer) - 4))							                                        //jmp    40024e <_start.lol>

TRAN_CMD (JA , JUMP (0xd))
TRAN_CMD (JB , JUMP (0xa))
TRAN_CMD (JE , JUMP (0x2))
TRAN_CMD (JAE, JUMP (0xb))
TRAN_CMD (JBE, JUMP (0xc))
TRAN_CMD (JNE, JUMP (0x3))

TRAN_CMD (CALL, DB (0xe8) DD (GETINT - (size_t)(_output_current) + (size_t) (_output_buffer) - 4))							                                        //callq  4002a1 <_ff>

TRAN_CMD (REV, DB  (0xc3))//1						    //retq

TRAN_CMD (SQRT, {							//8
		DW (0x2cdf) DB (0x24)					        //fild qword [rsp]
		DW (0xfad9)						                //fsqrt
		DW (0x3cdf) DB (0x24)					        //fistp qword [rsp]
		})
