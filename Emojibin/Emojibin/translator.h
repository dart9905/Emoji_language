#include <iostream>
#include <assert.h>

class translator
{
	private:
		void* _input_buffer   = nullptr;
		void* _output_buffer  = nullptr;
		void* _input_current  = nullptr;
		void* _output_current = nullptr;

		size_t _input_size    = 0;
		size_t _output_size   = 0;

		int get_int ();
		void make_header ();

	public:
		translator ();
		~translator ();
 
		void make_input_buffer ();
		void translate ();
		void make_output_file ();
        void make_bin ();

};

#include "translator.hpp"
