//
//  main.cpp
//  CodeToEmoji
//
//  Created by macbook on 20.12.2017.
//  Copyright © 2017 macbook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>

typedef char* TYPE_TREE;


const char* TREE_FILES1 = "../../../resources/save2.txt";

#include "../resources/tree.h"



Cell_t* EmojiCode  (Tree_t* Tree, Cell_t* cell, FILE* file);

int Emoji  (Cell_t* cell);

int EmojiSTR  (char* str);

int PrintS (FILE* file, char* str);


int main() {
    char str [] = "";
    Tree_t* Tree = TreeConstruct(str);
    
    TreeReadFiles("../../../resources/filetoemoji_read.txt", Tree, Tree->position_first_cell, LEFT_cell);
    
    FILE* file = fopen("../../../resources/filetoemoji_write.txt", "wt");
    EmojiCode  (Tree, Tree->position_first_cell->nextl, file);
    fclose(file);
    
    TreeDump(Tree, Tree->position_first_cell->nextl);
    
    TreeDestructor(Tree);
    
    return 0;
    
}



Cell_t* EmojiCode  (Tree_t* Tree, Cell_t* cell, FILE* file) {
    assert(Tree);
    assert(cell);
    //char str [CELL_SIZE_DATA] = "";
    if (strcmp(cell->data, "=") == 0) {
        Emoji  (cell->nextr);
        fprintf(file, "%s ", cell->nextr->data);
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
        cell = EmojiCode (Tree, cell->nextl, file);
        return cell->prev;
    }
    
    if ((strcmp(cell->data, "read") == 0) || (strcmp(cell->data, "print") == 0)) {
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
        Emoji  (cell->nextl);
        fprintf(file, "%s ", cell->nextl->data);
        return cell->prev;
    }
    
    if ((strcmp(cell->data, "write") == 0) || (strcmp(cell->data, "if") == 0)) {
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
        
        PrintS (file, "(");
        cell = EmojiCode (Tree, cell->nextl, file);
        PrintS (file, ")");
        
        PrintS (file, "{");
        fprintf(file, "\n");
        cell = EmojiCode (Tree, cell->nextr, file);
        PrintS (file, "}");
        fprintf(file, "\n");
        
        return cell->prev;
    }
    
    if ((cell->nextl != NULL) && (cell->data [0] == 'e') && (strcmp(cell->data, "end") != 0)) {
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
        PrintS (file, "(");
        cell = EmojiCode (Tree, cell->nextl, file);
        PrintS (file, ")");
        if (cell->nextr != NULL) {
            PrintS (file, "{");
            fprintf(file, "\n");
            cell = EmojiCode (Tree, cell->nextr, file);
            PrintS (file, "}");
            fprintf(file, "\n");
        }
        return cell->prev;
    }
    
    if (cell->nextl != NULL) {
        if (((strcmp(cell->data, "*") == 0) || (strcmp(cell->data, "/") == 0)) && ((strcmp(cell->nextl->data, "-") == 0) || (strcmp(cell->nextl->data, "+") == 0))) {
            PrintS (file, "(");
        }
        
        cell = EmojiCode (Tree, cell->nextl, file);
        
        if (((strcmp(cell->data, "*") == 0) || (strcmp(cell->data, "/") == 0)) && ((strcmp(cell->nextl->data, "-") == 0) || (strcmp(cell->nextl->data, "+") == 0))) {
            PrintS (file, ")");
        }
        if ((strcmp(cell->data, "!=") == 0) || (strcmp(cell->data, "==") == 0) ||
            (strcmp(cell->data, "<=") == 0) || (strcmp(cell->data, ">=") == 0) ||
            (strcmp(cell->data, "<") == 0) || (strcmp(cell->data, ">") == 0) ||
            (strcmp(cell->data, "*") == 0) || (strcmp(cell->data, "/") == 0) ||
            (strcmp(cell->data, "-") == 0) || (strcmp(cell->data, "+") == 0)) {
            Emoji  (cell);
            fprintf(file, "%s ", cell->data);
        }
        if (strcmp(cell->data, ";") == 0) {
            Emoji  (cell);
            fprintf(file, "%s", cell->data);
            if ((cell->nextr->nextl != NULL) && (cell->nextr->nextr != NULL)) {
                fprintf(file, "\n");
            }
        }
    }
    
    if (strcmp(cell->data, "end") == 0) {
        return cell->prev;
    }
    
    if (cell->nextr != NULL) {
        if (((strcmp(cell->data, "*") == 0) || (strcmp(cell->data, "/") == 0)) && ((strcmp(cell->nextr->data, "-") == 0) || (strcmp(cell->nextr->data, "+") == 0))) {
            PrintS (file, "(");
        }
        cell = EmojiCode (Tree, cell->nextr, file);
        
        if (((strcmp(cell->data, "*") == 0) || (strcmp(cell->data, "/") == 0)) && ((strcmp(cell->nextr->data, "-") == 0) || (strcmp(cell->nextr->data, "+") == 0))) {
            PrintS (file, ")");
        }
    }
    
    if (strcmp(cell->data, "begin") == 0) {
        
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
        PrintS (file, "{");
        fprintf(file, "\n");
        cell = EmojiCode (Tree, cell->prev->nextr, file);
        assert(strcmp(cell->data, "end") == 0);
        
        PrintS (file, "}");
        fprintf(file, "\n");
        return cell;
    }
    
    
    if ((cell->nextl == NULL) && (cell->nextr == NULL)) {
        Emoji  (cell);
        fprintf(file, "%s ", cell->data);
    }
    
    return cell->prev;
}



int EmojiSTR  (char* str) {
    
    #define DEF_CMD(str1, str2) \
    if (strcmp(str, str2) == 0) {\
        memcpy(str, str1, strlen(str1));\
        str [strlen(str1)] = '\0';\
    }
    #include "../../../resources/emoji.h"
    
    #undef DEF_CMD
    return 0;
}


int PrintS (FILE* file, char* str) {
    
    #define DEF_CMD(str1, str2) \
    if (strcmp(str, str2) == 0) {\
        fprintf(file, "%s", str1);\
    }
    #include "../../../resources/emoji.h"
    
    #undef DEF_CMD
    return 0;
}



int Emoji  (Cell_t* cell) {
    
    #define DEF_CMD(str1, str2) \
    if (strcmp(cell->data, str2) == 0) {\
        memcpy(cell->data, str1, strlen(str1));\
        cell->data [strlen(str1)] = '\0';\
    }
    #include "../../../resources/emoji.h"
    
    #undef DEF_CMD
    return 0;
};
