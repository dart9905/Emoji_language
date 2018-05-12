#include <iostream>
#include <assert.h>

class translator
{
	private:
		void* input_buffer   = nullptr;
		void* output_buffer  = nullptr;
		void* input_current  = nullptr;
		void* output_current = nullptr;

		size_t input_size    = 0;
		size_t output_size   = 0;

		int get_int ();
		void make_header ();

	public:
		translator ();
		~translator ();
 
		void make_input_buffer ();
		void translate ();
		void make_output_file ();

};

#include "translator.hpp"
