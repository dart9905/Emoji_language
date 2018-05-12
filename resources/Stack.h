#define ASSERT_OK( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_OK=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}





int stack_Construct (struct t_stack *name_stack, int print_stack_size);



int stack_Push (struct t_stack *name_stack,  DATA_TYPE element);



DATA_TYPE stack_Pop (struct t_stack *name_stack);



DATA_TYPE stack_Peek (struct t_stack *name_stack);



int stack_Check (struct t_stack *name_stack, int line);



int stack_Canary_update (struct t_stack *name_stack, int number_operation);



int stack_Canary_check (struct t_stack *name_stack);



int stack_Dump (struct t_stack *name_stack, int line);



char* stack_Last_operation (struct t_stack *name_stack);



int stack_Error (struct t_stack *name_stack);



int stack_Out (struct t_stack *name_stack);



int stack_Growth (struct t_stack *name_stack);



int stack_Plus (struct t_stack *name_stack, DATA_TYPE element);



int stack_Print_str (char str []);



int stack_Destructor (struct t_stack *name_stack);


enum CANARY {
    
    CANARY_POSITION = 1, ///< позиция в стеке ///< значение канарейкпи
    CANARY_SIZE = 2,     ///< колличество канареек в стеке
    CANARY_TEST_OK = 0,  ///< тест канарейки успешен
    CANARY_TEST_ERROR = 1///< тест канарейки провелен
    
};
const DATA_TYPE CANARY_VALUE = 666;

enum errors_or_warning {
    
    NO_ERROR = 0,              ///< нет ошибок
    E_MEMORY_ALLOCATION_ERROR, ///< ошибка создания стека в конструкторе из-за памяти
    E_STACK_EXPANSION,         ///< ошибка добавления элемента в стек из-за памяти
    W_STACK_OVERFLOW,          ///< предупреждение об добавлении элемента
    E_UNKNOWN_FUNCTION,        ///< неизвестная функция
    
};

enum stack_number_operation {
    
    S_Construct = 1,
    S_Push,
    S_Pop,
    S_Peek,
    S_Out,
    S_Destructor
    
};



struct t_stack {
    
    const DATA_TYPE CANARY_1 = 666;
    
    int canary_sum_data = 0;
    
    int stack_size = NULL;
    
    int pointer_position = NULL;
    
    int number = 0;
    
    
    int (*Construct)(t_stack*, int) = stack_Construct;
    
    int (*Push)(t_stack*, DATA_TYPE) = stack_Push;
    
    DATA_TYPE (*Pop)(t_stack*) = stack_Pop;
    
    DATA_TYPE (*Peek)(t_stack*) = stack_Peek;
    
    int (*Check)(t_stack*, int) = stack_Check;
    
    int (*Canary_update)(t_stack*, int) = stack_Canary_update;
    
    int (*Canary_check)(t_stack* ) = stack_Canary_check;
    
    int (*Dump)(t_stack*, int) = stack_Dump;
    
    char* (*Last_operation)(t_stack*) = stack_Last_operation;
    
    int (*Error_s)(t_stack*) = stack_Error;
    
    int (*Out)(t_stack*) = stack_Out;
    
    int (*Growth)(t_stack*) = stack_Growth;
    
    int (*Plus)(t_stack*, DATA_TYPE) = stack_Plus;
    
    int (*Print_str)(char []) = stack_Print_str;
    
    int (*Destructor)(t_stack* ) = stack_Destructor;
    
    
    const DATA_TYPE canary_2 = CANARY_1;
    
    int BUG = 0;
    
    unsigned int canary_sum_stack = 0;
    
    unsigned int last_operation = 0;
    
    DATA_TYPE *data_copy;
    DATA_TYPE *data = new DATA_TYPE [1];
};





int stack_Construct (struct t_stack *name_stack, int print_stack_size) {
    ASSERT_OK(name_stack);
    
    if (print_stack_size == NULL) {
        name_stack->stack_size = 10;
    } else {
        name_stack->stack_size = print_stack_size;
    }
    
    
    delete [] name_stack->data;
    name_stack->data = new DATA_TYPE [name_stack->stack_size + CANARY_SIZE];
    
    if (name_stack->data == 0) {
        return E_MEMORY_ALLOCATION_ERROR;
    }
    
    
    for (int i = 0; i < name_stack->stack_size; ++i)
    {
        name_stack->data [i + CANARY_POSITION] = 0;
    }
    
    name_stack->data [0] = CANARY_VALUE;
    name_stack->data [name_stack->stack_size + CANARY_POSITION] = CANARY_VALUE;
    name_stack->pointer_position = 0;
    
    name_stack->BUG = name_stack->Canary_update (name_stack, S_Construct);
    name_stack->Error_s(name_stack);
    
    name_stack->Dump(name_stack, __LINE__);
    
    return NO_ERROR;
}


int stack_Push (struct t_stack *name_stack, DATA_TYPE element) {
    ASSERT_OK(name_stack);
    name_stack->Check (name_stack, __LINE__);
    
    if (name_stack->pointer_position < name_stack->stack_size)
    {
        
        name_stack->Plus (name_stack, element);
        
        return NO_ERROR;
        
    } else {
        
        if (name_stack->Growth (name_stack) == E_STACK_EXPANSION) {
            return E_STACK_EXPANSION;
        }
        
        name_stack->data [name_stack->stack_size + CANARY_POSITION] = CANARY_VALUE;
        
        name_stack->Plus (name_stack, element);
        
        return W_STACK_OVERFLOW;
    }
}


DATA_TYPE stack_Pop (struct t_stack *name_stack) {
    
    ASSERT_OK(name_stack);
    name_stack->Check (name_stack, __LINE__);
    
    --name_stack->pointer_position;
    
    if (name_stack->pointer_position < 0) {
        ++name_stack->pointer_position;
        name_stack->Canary_update (name_stack, S_Pop);
        name_stack->Dump(name_stack, __LINE__);
        return NULL;
    }
    
    DATA_TYPE element = name_stack->data [name_stack->pointer_position + CANARY_POSITION];
    
    name_stack->data [name_stack->pointer_position + CANARY_POSITION] = 0;
    
    name_stack->Canary_update (name_stack, S_Pop);
    name_stack->Dump(name_stack, __LINE__);
    
    return element;
}


DATA_TYPE stack_Peek (struct t_stack *name_stack) {
    ASSERT_OK(name_stack);
    name_stack->Check (name_stack, __LINE__);
    name_stack->Canary_update (name_stack, S_Peek);
    
    name_stack->Dump(name_stack, __LINE__);
    
    if (name_stack->pointer_position < 1) {
        return NULL;
    }
    return name_stack->data [name_stack->pointer_position  + CANARY_POSITION - 1];
}


int stack_Check (struct t_stack *name_stack, int line) {
    ASSERT_OK(name_stack);
    
    if (name_stack->Canary_check (name_stack) == CANARY_TEST_ERROR)
    {
        name_stack->Print_str ("\nstack integrity violation\n\nCANARY_TEST_ERROR\n");
        
        ASSERT_OK(name_stack->Canary_check (name_stack) != CANARY_TEST_ERROR);
    } else {
        name_stack->Print_str ("\nstack intact\n\nCANARY_TEST_OK\n");
    }
    
    if (name_stack->Canary_check (name_stack) == CANARY_TEST_ERROR)
    {
        ASSERT_OK(name_stack->Canary_check (name_stack) != CANARY_TEST_ERROR);
    }
    
    return NO_ERROR;
}


int stack_Canary_update (struct t_stack *name_stack, int number_operation) {
    ASSERT_OK(name_stack);
    
    name_stack->last_operation = number_operation;
    name_stack->canary_sum_stack = 0;
    name_stack->canary_sum_data = 0;
    
    for (int i = 0; i < name_stack->stack_size + CANARY_SIZE; ++i) {
        
        name_stack->canary_sum_data += ((int*) name_stack->data) [i];
    }
    
    
    for (int i = 0; i == 0; ++i) {
        do {
            name_stack->canary_sum_stack += ((int*) name_stack) [i];
            ++i;
        } while (((DATA_TYPE*) name_stack) [i] != 666);
    }
    
    
    return NO_ERROR;
}


int stack_Canary_check (struct t_stack *name_stack) {
    ASSERT_OK(name_stack);
    
    if (name_stack->data [0] != CANARY_VALUE) {
        return CANARY_TEST_ERROR;
    }
    if (name_stack->data [name_stack->stack_size + CANARY_POSITION] != CANARY_VALUE) {
        return CANARY_TEST_ERROR;
    }
    
    
    int sum = 0;
    for (int i = 0; i == 0; ++i) {
        do {
            sum += ((int*) name_stack) [i];
            ++i;
        } while (((DATA_TYPE*) name_stack) [i] != 666);
    }
    if (sum != name_stack->canary_sum_stack) {
        return CANARY_TEST_ERROR;
    }
    
    
    
    
    sum = 0;
    for (int i = 0; i < name_stack->stack_size + CANARY_SIZE; ++i) {
        sum += ((int*) name_stack->data) [i];
    }
    if (sum != name_stack->canary_sum_data) {
        return CANARY_TEST_ERROR;
    }
    
    
    
    return CANARY_TEST_OK;
}


int stack_Dump (struct t_stack *name_stack, int line) {
    ASSERT_OK(name_stack);
    FILE *files = fopen (LOG_FILES_NAME, "at");
    
    fprintf(files, "==========t_stack==========\n\n");
    
    fprintf(files, "nover of the calling string %i\n\n", line);
    fprintf(files, "the last operation on the stack %s\n\n", name_stack->Last_operation(name_stack));
    
    
    fprintf (files, "name_stack->last_operation = %i\n\n", name_stack->last_operation);
    fprintf (files, "name_stack->canary_sum_data = %i\n\n", name_stack->canary_sum_data);
    fprintf (files, "name_stack->canary_sum_stack = %i\n\n", name_stack->canary_sum_stack);
    fprintf (files, "name_stack->stack_size = %i\n\n", name_stack->stack_size);
    fprintf (files, "name_stack->pointer_position = %i\n\n", name_stack->pointer_position);
    
    for (int i = 0; i < name_stack->stack_size + CANARY_SIZE; ++i) {
        fprintf(files, "name_stack->data[%i] = %i\n", i, name_stack->data[i]);
    }
    
    fprintf(files, "\n===========================\n\n");
    
    fclose(files);
    return 0;
}


char* stack_Last_operation (struct t_stack *name_stack) {
    switch (name_stack->last_operation) {
        case S_Construct:
        {
            return "Construct";
            break;
        }
        case S_Push:
        {
            return "Push";
            break;
        }
        case S_Pop:
        {
            return "Pop";
            break;
        }
        case S_Peek:
        {
            return "Peek";
            break;
        }
        case S_Out:
        {
            return "Out";
            break;
        }
        case S_Destructor:
        {
            return "Destructor";
            break;
        }
        default:
        {
            return "-";//E_UNKNOWN_FUNCTION;
        }
    }
}


int stack_Error (struct t_stack *name_stack) {
    ASSERT_OK(name_stack);
    
    if (NO_ERROR != name_stack->BUG) {
        
        switch (name_stack->BUG) {
            case E_MEMORY_ALLOCATION_ERROR:
            {
                name_stack->Print_str ("ERROR:\n   memory reservation error for the stack date in the constructor.\n\n");
                assert(0);
                break;
            }
            case E_STACK_EXPANSION:
            {
                name_stack->Print_str ("ERROR:\n   lack of memory for stack expansion in push.\n\n");
                assert(0);
                break;
            }
            case W_STACK_OVERFLOW:
            {
                name_stack->Print_str ("WARNING:\n   forced stack size increase by one.\n\n");
                break;
            }
            case E_UNKNOWN_FUNCTION:
            {
                name_stack->Print_str ("ERROR:\n   an unknown function could change the stack.\n\n");
                assert(0);
                break;
            }
            default:
            {
                name_stack->Print_str ("ERROR:   unknown error.\n\n");
                assert(0);
            }
        }
    }
    
    return 0;
}


int stack_Out (struct t_stack *name_stack) {
    
    name_stack->Canary_update (name_stack, S_Out);
    name_stack->Dump(name_stack, __LINE__);
    for (int i = 0; i < name_stack->stack_size + CANARY_SIZE;++i) {
        printf ("%i) %i\n",i, name_stack->data [i]);
    }
    printf("\n");
    return 0;
}


int stack_Growth (struct t_stack *name_stack) {
    ++name_stack->stack_size;
    name_stack->data_copy = new DATA_TYPE [name_stack->stack_size + CANARY_SIZE];
    
    if (name_stack->data_copy == 0) {
        return E_STACK_EXPANSION;
    }
    
    
    for (int i = 0; i < CANARY_SIZE + name_stack->stack_size - 1; ++i)
    {
        name_stack->data_copy [i] = name_stack->data [i];
    }
    
    
    delete [] name_stack->data;
    name_stack->data = new DATA_TYPE [name_stack->stack_size + CANARY_SIZE];
    if (name_stack->data_copy == 0) {
        return E_STACK_EXPANSION;
    }
    
    
    for (int i = 0; i < name_stack->stack_size + CANARY_SIZE; ++i)
    {
        name_stack->data [i] = name_stack->data_copy [i];
    }
    
    
    delete [] name_stack->data_copy;
    
    return NO_ERROR;
}


int stack_Print_str (char str []) {
    FILE *files = fopen (LOG_FILES_NAME, "at");
    
    fprintf(files, "==========t_stack==========\n\n");
    
    fprintf(files, "%s\n",str);
    
    fprintf(files, "\n===========================\n\n");
    fclose(files);
    return 0;
}


int stack_Plus (struct t_stack *name_stack, DATA_TYPE element) {
    name_stack->data [name_stack->pointer_position + CANARY_POSITION] = element;
    ++name_stack->pointer_position;
    ++name_stack->number;
    
    name_stack->BUG = name_stack->Canary_update (name_stack, S_Push);
    name_stack->Error_s(name_stack);
    name_stack->Dump(name_stack, __LINE__);
    return 0;
}


int stack_Destructor (struct t_stack *name_stack) {
    ASSERT_OK(name_stack);
    name_stack->Canary_update (name_stack, S_Destructor);
    name_stack->Dump(name_stack, __LINE__);
    delete [] name_stack->data;
    
    name_stack->canary_sum_data = 0;
    name_stack->stack_size = NULL;
    name_stack->pointer_position = NULL;
    name_stack->canary_sum_stack = 0;
    name_stack->last_operation = 0;
    
    return 0;
}

