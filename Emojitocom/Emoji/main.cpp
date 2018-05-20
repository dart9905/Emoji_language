#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <iostream>

const int MAX_COMMAND = 100, REGISTER_SZ = 10, CODE_SIZE = 100000, LABEL_SIZE = 20,
NUM_OF_LABEL = 50, PUSH_VAL = 2;

int binnary = 0;

struct Label_t
{
    char label[LABEL_SIZE] = {};
    int index = -1;
    int binnary = -1;
};

bool islabel            (FILE* input_file);
void compile            (FILE* input_file, const char* command, Label_t* labels, const int num_of_labels, int* buffer, int* index);
void compile_file       (const char* input_file_name, Label_t* labels, int* num_of_labels, int* buffer, int* i);
void write_to_file      (int* buffer, const int number_of_commands);

#define DEF_CMD(name, compiler_code)
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_REG
#undef DEF_CMD

void upstr(char* command) {
    
    for (int i = 0; command[i] != '\0'; i++) {
        command[i] = std::toupper(command[i]);
    }
}

int main ()
{
    Label_t* labels = (Label_t*) calloc (NUM_OF_LABEL, sizeof (*labels));
    assert (labels);
    
    int num_of_labels = 0;
    assert (&num_of_labels);
    
    int* buffer = (int*) calloc (CODE_SIZE, sizeof (*buffer));
    assert (buffer);
    
    int number_of_commands = 0;
    assert (&number_of_commands);
    
    char* input_file_name = (char*) calloc (FILENAME_MAX,  sizeof (*input_file_name));
    assert (input_file_name);
    
    scanf ("%s", input_file_name);
    
    //
    compile_file (input_file_name, labels, &num_of_labels, buffer, &number_of_commands);
    number_of_commands = 0;
    compile_file (input_file_name, labels, &num_of_labels, buffer, &number_of_commands);
    
    write_to_file (buffer, number_of_commands);
    free (input_file_name);
    free (buffer);
    return 0;
}

//---------------------------------------------------------------
//! Make file with numeric commands of command from input file
//!
//! @param [in] input_file_name    pointer on input file variable
//---------------------------------------------------------------
void compile_file (const char* input_file_name, Label_t* labels, int* num_of_labels, int* buffer, int* i)
{
    FILE* input_file = fopen (input_file_name, "rb");
    assert (input_file);
    
    char* command = (char*) calloc (MAX_COMMAND,  sizeof (*command));
    assert (command);
    
    while (strcmp(command, "END") != 0)
    {
        int label = islabel (input_file);
        assert (&label);
        
        fscanf (input_file, "%s", command);
        upstr(command);
        
        if (!label)
            compile (input_file, command, labels, *num_of_labels, buffer, i);
        
        else
        {
            strcpy ((labels[(*num_of_labels)]).label, command);
            (labels[(*num_of_labels)]).index = *i;
            ((labels[(*num_of_labels)++]).binnary) = binnary;
        }
        
    }
    binnary = 0;
    
    fclose (input_file);
}

int tell_register (const char* register_name)
{
#define DEF_CMD(name, compiler_code)
#define DEF_REG(name, code)\
code
    
#include "commands.h"
    
#undef DEF_REG
#undef DEF_CMD
    {
        printf ("UNKNOWN REGISTER NAME\n");
        assert (0);
    }
}

//-------------------------------------------------------------
//! Convert commands
//!
//! @param [in] input_file      pointer on input file variable
//! @param [in] command         string type command
//! @param [in] output_file     pointer on output file variable
//-------------------------------------------------------------
void compile (FILE* input_file, const char* command, Label_t* labels, const int num_of_labels, int* buffer, int* index)
{
#define DEF_CMD(name, compiler_code)\
compiler_code
#define DEF_REG(name, code)
    
#include "commands.h"
    
#undef DEF_REG
#undef DEF_CMD
    {
        printf ("UNKNOWN COMMAND: '%s'", command);
        assert (0);
    }
}

bool islabel (FILE* input_file)
{
    char* label_simbol = (char*) calloc (LABEL_SIZE, sizeof (*label_simbol));
    assert (label_simbol);
    int number = -1;
    assert (&number);
    
    fscanf (input_file, "\n%[:]%n", label_simbol, &number);
    free (label_simbol);
    
    return number != -1;
}

void write_to_file (int* buffer, const int number_of_commands)
{
    FILE* output_file = fopen ("CPU_commands.txt", "w");
    assert (output_file);
    
    fprintf (output_file, "Emoji_A1.1mac");
    
    fwrite (buffer, sizeof (int), number_of_commands, output_file);
    
    fclose (output_file);
}
