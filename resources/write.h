int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str);

Cell_t* CreatASSRet (Tree_t* Tree, Cell_t* cell, struct t_stack* stack, struct List_t* list, FILE* file);

Cell_t* CreatASSRetF (Cell_t* cell, FILE* file, int mark, int param);

int CreatFunVall (Cell_t* cell, FILE* file, struct t_stack* stack, struct List_t* list);

enum CreatFUN1 {
    PUSH_f = 0,
    POP_f = 1,
};

enum CreatFUN2 {
    LEFT_f = 0,
    RIGHT_f = 1,
};

#define DEF_CMD(functionT, declaration_cmd) \
if (strcmp(cell->data, #functionT) == 0) \
{ \
declaration_cmd\
} else

int SWITCH_ADD (Cell_t* cell, struct t_stack* stack, struct List_t* list, FILE* file) {
    
    
    
    #include "../resources/Comand.h"
    {
        CreatFunVall (cell, file, stack, list);
        
        if(('a' <= cell->data [0]) && (cell->data [0] <= 'z') && (cell->nextr != NULL) && (cell->nextl != NULL)) {
            
            if (cell->nextl->data [0] != '\0')
                CreatASSRetF (cell->nextl, file, PUSH_f, LEFT_f);
            fprintf(file,"RET\n\n");
        }
    }
    
    return 0;
}


#undef DEF_CMD




int CreatASS (Tree_t* Tree, Cell_t* cell, const char* str) {
    
    FILE* file = fopen(str, "wt");
    
    
    char str_l [] = "";
    List_t* list = ListConstruct(str_l);
    
    t_stack stack;
    stack.Construct (&stack, 10);
    
    CreatASSRet (Tree, cell, &stack, list, file);
    
    fclose(file);
    stack.Destructor(&stack);
    
    return 0;
}



Cell_t* CreatASSRet (Tree_t* Tree, Cell_t* cell, struct t_stack* stack, struct List_t* list, FILE* file) {
    
    assert(Tree);
    
    if (cell->nextl != NULL) {
        cell = CreatASSRet (Tree, cell->nextl, stack, list, file);
    }
    if (cell->nextr != NULL) {
        cell = CreatASSRet (Tree, cell->nextr, stack, list, file);
    }
    
    SWITCH_ADD (cell, stack, list, file);// функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    
    return cell->prev;
}



Cell_t* CreatASSRetF (Cell_t* cell, FILE* file, int mark, int param) {
    
    if (param == LEFT_f) {
        if (cell->nextl != NULL) {
            cell = CreatASSRetF (cell->nextl, file, mark, param);
        }
        if (cell->nextr != NULL) {
            cell = CreatASSRetF (cell->nextr, file, mark, param);
        }
    }
    
    if (param == RIGHT_f) {
        if (cell->nextr != NULL) {
            cell = CreatASSRetF (cell->nextr, file, mark, param);
        }
        if (cell->nextl != NULL) {
            cell = CreatASSRetF (cell->nextl, file, mark, param);
        }
    }
    
    if ((cell->nextl == NULL) && (cell->nextr == NULL)) {
        if (cell->data [0] != '\0') {
            if (mark == POP_f)
                fprintf(file,"POP %s\n", cell->data);
            if (mark == PUSH_f)
                fprintf(file,"PUSH %s\n", cell->data);
        }
    }
    
    return cell->prev;
}



int CreatFunVall (Cell_t* cell, FILE* file, struct t_stack* stack, struct List_t* list) {
    if (cell->prev != NULL)
        if (('a' <= cell->prev->data [0]) && (cell->prev->data [0] <= 'z') && ((cell->data [0] == ';') || (cell->data [0] == '\0'))) {
            if (cell->prev->nextl != NULL) {
                if (cell->prev->nextr != NULL) {
                    if (cell->prev->nextl == cell) {
                        
                        stack->Push(stack, stack->number + 1);\
                        fprintf(file, "%i :\n", stack->Peek(stack) + 100);
                        
                        ListAddBefore (list, list->position_first_cell, cell->prev->data);
                        list->position_first_cell->next->gotonumber = stack->Peek(stack) + 100;
                        if (cell->data [0] != '\0')
                            CreatASSRetF (cell, file, POP_f, LEFT_f);
                        
                    }
                } else {
                    
                    if (cell->data [0] != '\0')
                        CreatASSRetF (cell, file, PUSH_f, RIGHT_f);
                    
                    List_Cell_t* lcell = PositionCellValS (list, cell->prev->data);
                    
                    fprintf(file, "CALL %i\n", lcell->gotonumber);
                    
                    if (cell->data [0] != '\0')
                        CreatASSRetF (cell, file, POP_f, RIGHT_f);
                    
                }
            }
        }
    return 0;
}
