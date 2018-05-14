//
//  main.cpp
//  Language
//
//  Created by macbook on 28.11.2017.
//  Copyright © 2017 macbook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>



const char* TREE_FILES = "../../resources/save x!.txt";//read
const char* TREE_FILES1 = "../../resources/savefiletotree.txt";
const char* CODE_FILES1 = "../../resources/savefiletocodeasm.txt";
const char* LOG_FILES_NAME = "../../resources/logstack.txt";

const long int LI = 1000000000;
typedef char* TYPE_TREE;
typedef char* TYPE_LIST;
typedef int DATA_TYPE;

#include "../../resources/tree.h"
#include "../../resources/List.h"
#include "../../resources/Stack.h"
#include "../../resources/read.h"
#include "../../resources/write.h"





int DtoS (char* str, double var);

int OpVal (Tree_t* Tree, Cell_t* cell);

Cell_t* ValRet (Tree_t* Tree, Cell_t* cell, List_t* list1, List_t* list2);

char* SINT (char* str, long int num);

bool Emoji (char* str1, char* str2);

int Ten (int pos);






int main() {
    
    char str [] = "";
    Tree_t* Tree = TreeConstruct(str);
    
    long int number_of_char = 0;
    char* my_buffer = ReadFiles (TREE_FILES , &number_of_char);
    my_buffer = SINT (my_buffer, number_of_char);
    
    //printf("%s\n\n", my_buffer);
    
    Tree->cell = GetG0(Tree, my_buffer);
    Tree->position_first_cell = Tree->cell;
    
    TreeDump(Tree, Tree->cell);
    
    TreePrintFile(Tree, Tree->position_first_cell);
    
    OpVal (Tree, Tree->position_first_cell);
    
    //TreeDump(Tree, Tree->cell);
    
    CreatASS (Tree, Tree->position_first_cell, CODE_FILES1);
    
    TreeDestructor(Tree);
    
    delete [] my_buffer;
    
    return 0;
}



char* SINT (char* str, long int num) {
    
    char str0 [] = "";
    int j = 0;
    
    char* file_validation = new char [num] {};
    
    
#define DEF_CMD( name1, name2) \
if (Emoji (&(str [i]), name1)) {\
strcat(file_validation, name2);\
i += strlen(name1) - 1;\
} else
    
    
    for (int i = 0; i < num; ++i) {
        #include "../../resources/emoji.h"
            {
                char str2 [2] = {str[i], '\0'};
                strcat(file_validation, str2 );\
            }
    }
    
#undef DEF_CMD
    
    delete [] str;
    return file_validation;
}



bool Emoji (char* str1, char* str2) {
    for (int i = 0; i < strlen(str2); ++i) {
        if (*(str1 + i) != *(str2 + i)) {
            return false;
        }
    }
    return true;
}



int OpVal (Tree_t* Tree, Cell_t* cell) {
    assert(Tree);
    assert(cell);
    char str [] = "";
    
    List_t* list1 = ListConstruct(str);
    List_t* list2 = ListConstruct(str);
    
    ValRet (Tree, cell, list1, list2);
    
    ListDestructor (list1);
    ListDestructor (list2);
    
    return 0;
}



Cell_t* ValRet (Tree_t* Tree, Cell_t* cell, List_t* list1, List_t* list2) {
    
    assert(Tree);
    
    if (cell->nextl != NULL) {
        cell = ValRet (Tree, cell->nextl, list1, list2);
    }
    
    if (cell->nextr != NULL) {
        cell = ValRet (Tree, cell->nextr, list1, list2);
    }
    if ((strcmp(cell->data, "begin") != 0) && (strcmp(cell->data, "print") != 0) &&
        (strcmp(cell->data, "read") != 0) && (strcmp(cell->data, "if") != 0) &&
        (strcmp(cell->data, "while") != 0)) {
        
        if ((cell->nextr == NULL) && (cell->nextl == NULL)) {
            if (('a' <= cell->data [0]) && (cell->data [0] <= 'z')) {
                List_Cell_t* lcell = PositionCellValS (list1, cell->data);
                int num = 0;
                
                if (lcell) {
                    num = lcell->number;
                } else {
                    char* str = new char {};
                    memcpy(str, cell->data, strlen(cell->data));
                    ListAddBefore (list1, list1->position_first_cell, str);
                    num = list1->position_first_cell->next->number;
                }
                
                char str [CELL_SIZE_DATA] = "";
                str [0] = '[';
                int len = 1;
                
                while (num / (10 * len) > 0) {++len;}
                for (int i = 1; i < len + 1; ++i) {
                    str [i] = '0' + num / (Ten (len - i + 1));
                    num = num - (num / (Ten (len - i + 1)) * (Ten (len - i + 1)));
                }
                
                str [len + 1] = ']';
                str [len + 2] = '\0';
                memcpy(cell->data, str, len + 3);
                
            }
        }
    }
    return cell->prev;
}



int Ten (int pos) {
    int val = 1;
    for (int i = 1; i < pos; ++i)
        val *= 10;
    return val;
}



int DtoS (char* str, double var) {
    
    int i = 0;
    assert(str);
    str [0] = '\0';
    
    if (var < 0) {
        var = (-1) * var;
        str [i] = '-';
        ++i;
    }
    
    long int maxd = 1;
    long int maxp = 1;
    long int j = 0;
    long int pov = var;
    long int div = var * LI - pov * LI;
    long int longdiv = LI;
    
    
    
    while((j == 0) && (div > 0))
    {
        div = div / 10;
        j = div % 10;
        longdiv = longdiv / 10;
    }
    
    longdiv = longdiv / 10;
    
    while (maxp <= pov) maxp = maxp * 10;
    maxp = maxp / 10;
    
    while (maxd <= div) maxd = maxd * 10;
    maxd = maxd / 10;
    
    while (maxp > 0) {
        str [i] = pov / maxp + '0';
        if (pov > 0)
            pov = pov - (pov / maxp) * maxp;
        maxp = maxp / 10;
        ++i;
    }
    if (maxd > 0) {
        str [i] = '.';
        ++i;
        
        while (longdiv != maxd) {
            str [i] = '0';
            ++i;
            longdiv = longdiv / 10;
        }
        
        while (div > 0) {
            str [i] = div / maxd + '0';
            div = div - (div / maxd) * maxd;
            maxd = maxd / 10;
            ++i;
        }
    }
    if (i == 0) {
        str [i] = '0';
        ++i;
    }
    str [i] = '\0';
    
    return i;
    
}
