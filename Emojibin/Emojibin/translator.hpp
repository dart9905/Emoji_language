#define TRAN_CMD(number, command)

#include "translator_commands.h"

#undef TRAN_CMD

const int SIGNSIZE = 13;
const int MAX_SIZE = 100000;
const int HEADER_SIZE = 210;

size_t size_of_file (FILE* file);

void translator::make_input_buffer ()
{
	FILE* input_file = fopen ("CPU_commands.txt", "r");
	assert (input_file);

	_input_size = size_of_file (input_file);

	_input_buffer = (char*) calloc (1, _input_size);
	assert (_input_buffer);

	fread (_input_buffer, 1, _input_size, input_file);

	_input_current = (char*)_input_buffer + SIGNSIZE;

	fclose (input_file);
}

void translator::translate ()
{
	_output_buffer = calloc (MAX_SIZE, 1);
	assert (_output_buffer);

	_output_current = _output_buffer;

	//DW (0x8948) DB (0xe5)			    //mov rbp, rsp
	//DW (0x8148) DB (0xec) DD (0x400)	//sub rsp, 1024d

	_output_buffer = (char*)_output_buffer + 10;

	while ((size_t) ((size_t)(_input_current) - (size_t)(_input_buffer)) <= _input_size)
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

	_output_buffer = (char*)_output_buffer - 10;
	_output_size = (size_t) ((size_t)_output_current - (size_t)_output_buffer);
}

void translator::make_output_file ()
{
    void* output_buffer = calloc (_output_size + HEADER_SIZE, 1);
	assert (output_buffer);

	memcpy ((char*)output_buffer + HEADER_SIZE, _output_buffer,  _output_size);
	free (_output_buffer);
	
	_output_buffer = output_buffer;
	_output_current = output_buffer;

	make_header ();

	FILE* output_file = fopen ("run", "w");
	assert (output_file);

	fwrite (_output_buffer, 1, _output_size + HEADER_SIZE, output_file);
	
	fclose (output_file);
}

translator::translator () {}

translator::~translator ()
{
	free (_input_buffer);
	free (_output_buffer);
}

int translator::get_int ()
{
	int temp = 0;
	memcpy (&temp, _input_current, sizeof(int));
	_input_current = (char*)_input_current + sizeof(int);

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
    /*
    for (int i = 0; i<HEADER_SIZE; i++)
        DB (0x90)
    //*/
    //*
	DB (0x7f)
	DB ('E')
	DB ('L')
	DB ('F')
	DB (0x02)
	DB (0x01)
	DB (0x01)
	DB (0x00)           //8
	DQ (0x00)           //8
	DW (0x02)           //
	DW (0x3e)           //4
	DD (0x01)           //4
	DQ (0x4000b0)       //8
	DQ (0x40)           //8
	DQ (0x00)           //8
	DD (0x00)           //4
	DW (0x40)           //2
	DW (0x38)           //2
	DW (0x02)           //2
	DW (0x00)           //2
	DW (0x00)           //2
	DW (0x00)           //2
	DD (0x01)           //4
	DD (0x05)           //4
	DQ (0x00)           //8
	DQ (0x400000)           //8
	DQ (0x400000)           //8
	DQ (0xd2 + _output_size)           //8
	DQ (0xd2 + _output_size)           //8
	DQ (0x10)           //8
	DD (0x01)            //4
	DD (0x06)           //4
	DQ (0xb2)           //8
	DQ (0x6000b2)           //8
	DQ (0x6000b2)           //8
	DQ (0x20)           //8
	DQ (0x20)           //8
	DQ (0x10)           //8
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
	DB ('f')           //18
    //*/
}
