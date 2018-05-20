///MAKER OF COMMANDS OF COMPILER
//------------------------------

#include "enums.h"

#define COMMAND(name)\
        if (strcmp (command, #name) == 0)

#define REGISTER(name)\
        if (strcmp (register_name, #name) == 0)\
            return name;\
        else

#define SIMPLE_COMMAND(name, size)\
        COMMAND(name)\
	{\
        buffer[(*index)++] = name;\
	binnary += size;}\
    else

#define JUMP_COMMAND(name, size)\
        COMMAND(name)\
    {\
        char* label = (char*) calloc (LABEL_SIZE, sizeof (*label));\
        assert (label);\
\
        fscanf (input_file, " :%s", label);\
\
        buffer[(*index)++] = name;\
\
        int point = -1;\
        assert (&point);\
\
        for (int i = 0; i < num_of_labels; i++)\
        {\
            if (strcmp (label, labels[i].label) == 0)\
                point = labels[i].binnary;\
        }\
	binnary += size;\
\
        buffer[(*index)++] = point;\
    }\
\
    else


#define REGISTER_NAME\
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));\
        assert (register_name);\
\
        int number = -1;\
        assert (&number);\
\
        fscanf (input_file, " %[ABCDXabcdx] %n", register_name, &number);

#define NOT_WRONG_COMMAND\
        if (number == -1)\
            {\
                printf ("WRONG COMMAND: '%s'\n", command);\
                assert (0);\
            }\
            else

#define STACK_SMALL\
        if (cpu.stck.Size () < MIN_STACK)\
            {\
                printf ("Can't compare 2 elements, stack size < 2\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\
            else

#define BAD_JUMPING\
        if (buffer[i + 1] == -1)\
            {\
                printf ("Bad jumping\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\
        else




DEF_CMD(PUSH, COMMAND(PUSH)
    {
        //REGISTER_NAME
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));
        assert (register_name);

        int number = -1;
        assert (&number);

        getc (input_file);

        fscanf (input_file, "[%[ABCDXabcdx]]%n", register_name, &number);
        
        upstr(register_name);
        
        if (number != -1)
        {
            buffer[(*index)++] = PUSH;
            buffer[(*index)++] = REGRAM;
            buffer[(*index)++] = tell_register (register_name);
	    binnary += 21;
        }

        else
        {
            fscanf (input_file, "%[ABCDXabcdx]%n", register_name, &number);
            upstr(register_name);


            if (number == -1)
            {
                double value = 0;
                assert (&value);

                fscanf (input_file, "%lf%n", &value, &number);
			
                NOT_WRONG_COMMAND

                if (getc (input_file) != ']')
                {

                    buffer[(*index)++] = PUSH;
                    buffer[(*index)++] = VAL;
                    buffer[(*index)++] = (int)value;
		    binnary += 5;
                }
                else
                {
                    buffer[(*index)++] = PUSH;
                    buffer[(*index)++] = RAM;
                    buffer[(*index)++] = (int)value;
		    binnary += 14;
                }
            }
            else
            {
                buffer[(*index)++] = PUSH;
                buffer[(*index)++] = REG;
                buffer[(*index)++] = tell_register (register_name);
		binnary += 1;
            }
        }
        free (register_name);
    }

    else)


DEF_CMD(MOV, COMMAND(MOV)
        {
            //REGISTER_NAME
            char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));
            assert (register_name);
            
            int number = -1;
            assert (&number);
            
            
            buffer[(*index)++] = MOV;
            
            
            
            for (int i = 0; i < 2; i++) {
                
                getc (input_file);
                if (i == 1)
                    getc (input_file);
            
                fscanf (input_file, "[%[ABCDXabcdx]]%n", register_name, &number);
                upstr(register_name);
                
                if (number != -1)
                {
                    buffer[(*index)++] = REGRAM;
                    buffer[(*index)++] = tell_register (register_name);
                    //binnary += 21;
                }
                
                else
                {
                    fscanf (input_file, "%[ABCDXabcdx]%n", register_name, &number);
                    upstr(register_name);
                    if (number == -1)
                    {
                        double value = 0;
                        assert (&value);
                        
                        fscanf (input_file, "%lf%n", &value, &number);
                        
                        NOT_WRONG_COMMAND
                        
                        if (getc (input_file) != ']')
                        {
                            buffer[(*index)++] = VAL;
                            buffer[(*index)++] = (int)value;
                            //binnary += 5;
                        }
                        else
                        {
                            buffer[(*index)++] = RAM;
                            buffer[(*index)++] = (int)value;
                            //binnary += 14;
                        }
                    }
                    else
                    {
                        buffer[(*index)++] = REG;
                        buffer[(*index)++] = tell_register (register_name);
                        binnary += 1;
                    }
                }
                register_name[0] = '\0';
                number = -1;
                
            }
            
            free (register_name);
            
            
        }
        
        else)


DEF_CMD(POP, COMMAND(POP)
    {
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));
        assert (register_name);

        int number = -1;
        assert (&number);
        getc (input_file);

        fscanf (input_file, "[%[ABCDXabcdx]]%n", register_name, &number);
        upstr(register_name);
        if (number != -1)
        {
            buffer[(*index)++] = POP;
            buffer[(*index)++] = REGRAM;
            buffer[(*index)++] = tell_register (register_name);
	    binnary += 20;
        }
        else
        {
            fscanf (input_file, "%[ABCDXabcdx]%n", register_name, &number);
            upstr(register_name);
            if (number == -1)
            {
                int value = 0;
                assert (&value);

                fscanf (input_file, "%d]%n", &value, &number);

                NOT_WRONG_COMMAND

                buffer[(*index)++] = POP;
                buffer[(*index)++] = RAM;
                buffer[(*index)++] = value;
		binnary += 14;
            }
            else
            {
                buffer[(*index)++] = POP;
                buffer[(*index)++] = REG;
                buffer[(*index)++] = tell_register (register_name);	
		binnary += 1;
            }
        }
        free (register_name);
    }

    else)

DEF_CMD(ADD, SIMPLE_COMMAND(ADD, 6))//6
DEF_CMD(SUB, SIMPLE_COMMAND(SUB, 6))//6
DEF_CMD(MUL, SIMPLE_COMMAND(MUL, 8))//8
DEF_CMD(DIV, SIMPLE_COMMAND(DIV, 11))
DEF_CMD(OUT, SIMPLE_COMMAND(OUT, 178))

DEF_CMD(END, SIMPLE_COMMAND(END, 17))//17
DEF_CMD(IN,  SIMPLE_COMMAND(IN, 113))

DEF_CMD(SQRT, SIMPLE_COMMAND(SQRT, 0))
DEF_CMD(SIN,  SIMPLE_COMMAND(SIN, 0))
DEF_CMD(COS,  SIMPLE_COMMAND(COS, 0))

DEF_CMD(RET, SIMPLE_COMMAND(RET, 1))

DEF_CMD(JE,  JUMP_COMMAND(JE,  11))
DEF_CMD(JNE, JUMP_COMMAND(JNE, 11))
DEF_CMD(JA,  JUMP_COMMAND(JA,  11))
DEF_CMD(JAE, JUMP_COMMAND(JAE, 11))
DEF_CMD(JB,  JUMP_COMMAND(JB,  11))
DEF_CMD(JBE, JUMP_COMMAND(JBE, 11))
DEF_CMD(JMP, JUMP_COMMAND(JMP, 5 ))

DEF_CMD(CALL, JUMP_COMMAND(CALL, 5))

DEF_REG(AX, REGISTER(AX))
DEF_REG(BX, REGISTER(BX))
DEF_REG(CX, REGISTER(CX))
DEF_REG(DX, REGISTER(DX))

#undef BAD_JUMPING
#undef STACK_SMALL
#undef NOT_WRONG_COMMAND
#undef REGISTER_NAME
#undef JUMP_COMMAND
#undef SIMPLE_COMMAND
#undef REGISTER
#undef COMMAND
