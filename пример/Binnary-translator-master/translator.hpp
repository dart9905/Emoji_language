#define TRAN_CMD(number, command)

#include "translator_commands.h"

#undef TRAN_CMD

const int SIGNSIZE = 7;
const int MAX_SIZE = 100000;
const int HEADER_SIZE = 210;

size_t size_of_file (FILE* file);

void translator::make_input_buffer ()
{
	FILE* input_file = fopen ("CPU_commands.txt", "r");
	assert (input_file);

	this -> input_size = size_of_file (input_file);

	this -> input_buffer = (char*) calloc (1, this -> input_size);
	assert (this -> input_buffer);

	fread (this -> input_buffer, 1, this -> input_size, input_file);

	/*for (int i = 8; i < this -> input_size; i++)
	{
		printf ("'%c'", *((char*) (this -> input_buffer + i)));
	}*/

	this -> input_current = this -> input_buffer + SIGNSIZE;	

	fclose (input_file);
}

void translator::translate ()
{
	this -> output_buffer = calloc (MAX_SIZE, 1);
	assert (this -> output_buffer);

	this -> output_current = this -> output_buffer;

	DW (0x8948) DB (0xe5)			//mov rbp, rsp
	DW (0x8148) DB (0xec) DD (0x400)	//sub rsp, 1024d

	this -> output_buffer += 10;

	while ((size_t) ((size_t)(this -> input_current) - (size_t)(this -> input_buffer)) <= this -> input_size)
	{
		int temp = get_int ();

		#define TRAN_CMD(number, command)\
			case (number):\
			{\
				command\
					\
				break;\
			}
		
		switch (temp)
		{
			#include "translator_commands.h"
		}
		
		#undef TRAN_CMD
	}

	this -> output_buffer -= 10;
	this -> output_size = (size_t) ((size_t)this -> output_current - (size_t)this -> output_buffer);
}

void translator::make_output_file ()
{
	void* output_buffer = calloc (this -> output_size + HEADER_SIZE, 1);
	assert (output_buffer);

	memcpy (output_buffer + HEADER_SIZE, this -> output_buffer, this -> output_size);
	free (this -> output_buffer);
	
	this -> output_buffer = output_buffer;
	this -> output_current = output_buffer;

	make_header ();

	FILE* output_file = fopen ("run", "w");
	assert (output_file);

	fwrite (this -> output_buffer, 1, this -> output_size + HEADER_SIZE, output_file);
	
	fclose (output_file);
}

translator::translator () {}

translator::~translator ()
{
	free (this -> input_buffer);
	free (this -> output_buffer);
}

int translator::get_int ()
{
	int temp = 0;
	memcpy (&temp, this -> input_current, sizeof(int));
	this -> input_current += sizeof(int);

	return temp;
}

size_t size_of_file (FILE* file)
{
	fseek(file, 0, SEEK_END);
	size_t file_length = ftell(file);
	rewind(file);

	return file_length;
}

void translator::make_header ()
{
	DB (0x7f)
	DB ('E')
	DB ('L')
	DB ('F')
	DB (0x02)
	DB (0x01)
	DB (0x01)
	DB (0x00)
	DQ (0x00)
	DW (0x02)
	DW (0x3e)
	DD (0x01)
	DQ (0x4000b0)
	DQ (0x40)
	DQ (0x00)
	DD (0x00)
	DW (0x40)
	DW (0x38)
	DW (0x02)
	DW (0x00)
	DW (0x00)
	DW (0x00)
	DD (0x01)                                 
	DD (0x05)                                
	DQ (0x00)                                 
	DQ (0x400000)                              
	DQ (0x400000)                              
	DQ (0xd2 + this -> output_size)                
	DQ (0xd2 + this -> output_size)               
	DQ (0x10)                                  
	DD (0x01)                                 
	DD (0x06)                                  
	DQ (0xb2)                                  
	DQ (0x6000b2)                  
	DQ (0x6000b2)                             
	DQ (0x20)                                 
	DQ (0x20)                           
	DQ (0x10)                                 
	DB (0xeb)                          
	DB (0x20)
	DB ('0')                                  
	DB ('1')
	DB ('2')
	DB ('3')
	DB ('4')
	DB ('5')
	DB ('6')
	DB ('7')
	DB ('8')
	DB ('9')
	DB ('a')
	DB ('b')
	DB ('c')
	DB ('d')
	DB ('e')
	DB ('f')
}
