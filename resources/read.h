Cell_t* GetG0 (Tree_t* Tree, const char* pSTR);

Cell_t* GetE (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetT (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetS (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetP (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetN (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetEQ (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetOR (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetIF (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetSIGN (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetSTRF (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetSK (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetBE (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetRP (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetEmojiStr (Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* GetEmoji(Tree_t* Tree, const char* pSTR, int* pPOS);

Cell_t* Creat_Cell (Tree_t* Tree, Cell_t* cell1, Cell_t* cell2, Cell_t* cell3, char* str);



int Space (const char* pSTR, int* pPOS);



Cell_t* GetG0 (Tree_t* Tree, const char* pSTR) {
    
    int POS = 0;
    //pSTR = "";
    
    Cell_t* cell_new = GetOR(Tree, pSTR, &POS);
    
    assert(cell_new);
    //assert(0);
    assert(pSTR[POS] == '\0');
    
    return cell_new;
}



Cell_t* GetOR (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetSK(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == ';') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetOR(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    return cell_new3;
    
}



Cell_t* GetSK (Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    Space (pSTR, pPOS);
    if (pSTR [*pPOS] == '{') {
        Space (pSTR, pPOS);
        ++*pPOS;
        Cell_t* cell_new = GetOR(Tree, pSTR, pPOS);
        Space (pSTR, pPOS);
        
        assert(pSTR [*pPOS] == '}');
        ++*pPOS;
        Space (pSTR, pPOS);
        return cell_new;
    }
    return GetEQ(Tree, pSTR, pPOS);
    
}



Cell_t* GetIF (Tree_t* Tree, const char* pSTR, int* pPOS) {
    char* op = new char [3];
    
    
    Cell_t* cell_new3 = GetF1(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    
    Cell_t* cell_new = GetSIGN(Tree, pSTR, pPOS);
    assert(cell_new);
    Cell_t* cell_new2 = NULL;
    
    cell_new2 = GetSK(Tree, pSTR, pPOS);
    assert(cell_new2);
    
    
    cell_new3->nextl = cell_new;
    cell_new3->nextr = cell_new2;
    cell_new3->nextl->prev = cell_new3;
    cell_new3->nextr->prev = cell_new3;
    
    return cell_new3;
    
}



Cell_t* GetSIGN (Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    assert(pSTR [*pPOS] == '(');
    ++*pPOS;
    
    Cell_t* cell_new = GetE(Tree, pSTR, pPOS);
    
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [3];
    
    assert(cell_new);
    
    if ((pSTR [*pPOS] == '!') || (pSTR [*pPOS] == '>') || (pSTR [*pPOS] == '<') || ((pSTR [*pPOS] == '=') && (pSTR [*pPOS+1] == '='))) {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        if (pSTR [*pPOS] == '=') {
            op [1] = pSTR [*pPOS];
            op [2] = '\0';
            ++*pPOS;
        }
        cell_new2 = GetE(Tree, pSTR, pPOS);
        assert(pSTR [*pPOS] == ')');
        ++*pPOS;
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    return cell_new3;
}



Cell_t* GetEQ (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetE(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '=') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetEQ(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new2, cell_new, cell_new3, op);
        
    }
    return cell_new3;
}



Cell_t* GetE (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetT(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '+' || pSTR [*pPOS] == '-') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetE(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    return cell_new3;
}



Cell_t* GetT(Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetS(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '*' || pSTR [*pPOS] == '/') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetT(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    
    return cell_new3;
}



Cell_t* GetS (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Cell_t* cell_new = GetP(Tree, pSTR, pPOS);
    Cell_t* cell_new2 = NULL;
    Cell_t* cell_new3 = cell_new;
    char* op = new char [2];
    
    assert(cell_new);
    
    if (pSTR [*pPOS] == '^') {
        op [0] = pSTR [*pPOS];
        op [1] = '\0';
        ++*pPOS;
        
        cell_new2 = GetS(Tree, pSTR, pPOS);
        assert(cell_new2);
        
        
        cell_new3 = Creat_Cell (Tree, cell_new, cell_new2, cell_new3, op);
        
    }
    
    return cell_new3;
    
}




Cell_t* GetP (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Space (pSTR, pPOS);
    
    if ((pSTR [*pPOS] =='b') && (pSTR [*pPOS + 1] =='e') && (pSTR [*pPOS + 2] =='g')) {
        return GetBE (Tree, pSTR, pPOS);
        
    } else {
        if (pSTR [*pPOS] =='(') {
            Space (pSTR, pPOS);
            ++*pPOS;
            Cell_t* cell_new = GetE (Tree, pSTR, pPOS);
            Space (pSTR, pPOS);
            assert(pSTR [*pPOS] == ')');
            ++*pPOS;
            Space (pSTR, pPOS);
            return cell_new;
            
            
        } else {
            if ((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z'))) {
                
                
                if (((pSTR [*pPOS] == 'i') && (pSTR [*pPOS+1] == 'f')) || ((pSTR [*pPOS] == 'w') && (pSTR [*pPOS+1] == 'h'))) {
                    return GetIF(Tree, pSTR, pPOS);
                } else {
                    if (((pSTR [*pPOS] == 'r') && (pSTR [*pPOS+1] == 'e') && (pSTR [*pPOS+2] == 'a')) ||
                        ((pSTR [*pPOS] == 'p') && (pSTR [*pPOS+1] == 'r') && (pSTR [*pPOS+2] == 'i')) ||
                        ((pSTR [*pPOS] == 'r') && (pSTR [*pPOS+1] == 'e') && (pSTR [*pPOS+2] == 't'))) {
                        return GetRP(Tree, pSTR, pPOS);
                    } else  {
                        return GetSTRF(Tree, pSTR, pPOS);
                    }
                }
                } else {
                    
                    if ((('0' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= '9')) || (pSTR [*pPOS] == '+') || (pSTR [*pPOS] == '-')) {
                        return GetN(Tree, pSTR, pPOS);
                    } else {
                        if ((pSTR [*pPOS] != ')' && pSTR [*pPOS] != '}')) {
                            return GetEmojiStr(Tree, pSTR, pPOS);
                        } else {
                            return GetN(Tree, pSTR, pPOS);
                        }
                    }
                }
            }
        }
        
    
    
    printf("NULL\n");
    return NULL;
}



Cell_t* GetSTRF (Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    
    Space (pSTR, pPOS);
    Cell_t* cell_new = GetF1(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    assert(cell_new);
    
    if (pSTR [*pPOS] == '(') {
        
        ++*pPOS;
        
        cell_new->nextl = GetOR(Tree, pSTR, pPOS);
        Space (pSTR, pPOS);
        
        if (pSTR [*pPOS] == ',') {
            ++*pPOS;
            cell_new->nextr = GetE(Tree, pSTR, pPOS);
            Space (pSTR, pPOS);
            cell_new->nextr->prev = cell_new;
        }
        
        assert(pSTR [*pPOS] == ')');
        ++*pPOS;
        assert(cell_new->nextl);
        cell_new->nextl->prev = cell_new;
        Space (pSTR, pPOS);
        
        
        
        
        if (pSTR [*pPOS] == '{') {
            cell_new->data;
            Cell_t* cell_new3 = GetSK(Tree, pSTR, pPOS);
            Space (pSTR, pPOS);
            
            cell_new->nextr = cell_new3;
            cell_new->nextr->prev = cell_new;
        }
        
    }
    
    
    return cell_new;
}



Cell_t* GetN (Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    Space (pSTR, pPOS);
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    int i = 0;
        
    
    if (((pSTR [*pPOS] == '+') || (pSTR [*pPOS] == '-')) && ('0' <= pSTR [*pPOS + 1] && pSTR [*pPOS + 1] <= '9')) {
        str [i] = pSTR [*pPOS];
        ++*pPOS;
        ++i;
    }
    
    while ('0' <= pSTR [*pPOS] && pSTR [*pPOS] <= '9') {
        str [i] = pSTR [*pPOS];
        ++*pPOS;
        ++i;
    }
    
    if (pSTR [*pPOS] == '.') {
        while ('0' <= pSTR [*pPOS] && pSTR [*pPOS] <= '9') {
            str [i] = pSTR [*pPOS];
            ++i;
            ++*pPOS;
        }
        
    }
    str [i] = '\0';
    memcpy(val_s, str, strlen(str));
    
    Cell_t* cell_new = CellNew(Tree);
    cell_new->data = val_s;
    
    
    Space (pSTR, pPOS);
    
    return cell_new;
}



Cell_t* GetF1(Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    Space (pSTR, pPOS);
    
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    int i = 0;
    if (((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z')))
        && (pSTR [*pPOS] != '(')) {
        
        while ((('0' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= '9')) || ((('a' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'z')) || (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z')))
               && (pSTR [*pPOS] != '(')) {
            
            if (('A' <= pSTR [*pPOS]) && (pSTR [*pPOS] <= 'Z')) {
                str [i] = pSTR [*pPOS] - ('A' - 'a');
            } else
                str [i] = pSTR [*pPOS];
            
            ++i;
            ++*pPOS;
        }
    }
    
    
    str [i] = '\0';
    
    memcpy(val_s, str, strlen(str));
    
    Cell_t* cell_new = CellNew(Tree);
    cell_new->data = val_s;
    
    Space (pSTR, pPOS);
    
    return cell_new;
}



Cell_t* GetBE (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Space (pSTR, pPOS);
    Cell_t* cell_new = GetF1(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    Cell_t* cell_new2 = GetSK(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    
    //assert(pSTR [*pPOS] == 'E' && pSTR [*pPOS + 1] == 'N' && pSTR [*pPOS + 2] == 'D');
    Cell_t* cell_new3 = CellNew(Tree);
    cell_new3->data = "end";
    
    cell_new3->nextl = cell_new;
    cell_new3->nextr = cell_new2;
    cell_new3->nextl->prev = cell_new3;
    cell_new3->nextr->prev = cell_new3;
    
    Space (pSTR, pPOS);
    return cell_new3;
}



Cell_t* GetRP (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Space (pSTR, pPOS);
    Cell_t* cell_new3 = GetF1(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    Cell_t* cell_new = GetP(Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    
    cell_new3->nextl = cell_new;
    cell_new3->nextl->prev = cell_new3;
    
    Space (pSTR, pPOS);
    return cell_new3;
}



int Space (const char* pSTR, int* pPOS) {
    
    while ((pSTR [*pPOS] == ' ') || (pSTR [*pPOS] == '\n') || (pSTR [*pPOS] == '\t') || (pSTR [*pPOS] == '\r')) {
        ++*pPOS;
    }
    
    return 0;
}



Cell_t* GetEmojiStr (Tree_t* Tree, const char* pSTR, int* pPOS) {
    Space (pSTR, pPOS);
    Cell_t* cell_new = GetEmoji (Tree, pSTR, pPOS);
    Space (pSTR, pPOS);
    assert(cell_new);
    
    if (pSTR [*pPOS] == '(') {
        
        ++*pPOS;
        
        cell_new->nextl = GetOR(Tree, pSTR, pPOS);
        Space (pSTR, pPOS);
        
        if (pSTR [*pPOS] == ',') {
            ++*pPOS;
            cell_new->nextr = GetE(Tree, pSTR, pPOS);
            Space (pSTR, pPOS);
            cell_new->nextr->prev = cell_new;
        }
        
        assert(pSTR [*pPOS] == ')');
        ++*pPOS;
        assert(cell_new->nextl);
        cell_new->nextl->prev = cell_new;
        Space (pSTR, pPOS);
        
        
        
        
        if (pSTR [*pPOS] == '{') {
            cell_new->data;
            Cell_t* cell_new3 = GetSK(Tree, pSTR, pPOS);
            Space (pSTR, pPOS);
            
            cell_new->nextr = cell_new3;
            cell_new->nextr->prev = cell_new;
        }
        
    }
    
    
    return cell_new;
}



Cell_t* GetEmoji (Tree_t* Tree, const char* pSTR, int* pPOS) {
    
    
    Space (pSTR, pPOS);
    char* val_s = new char [CELL_SIZE_DATA];
    char str [CELL_SIZE_DATA] = "";
    str [0] = 'e';
    int i = 1;
    
    while ((pSTR [*pPOS] != ' ') && (pSTR [*pPOS] != '\n') && (pSTR [*pPOS] != '\0') && (pSTR [*pPOS] != '\r')
            && (pSTR [*pPOS] != '\t')) {
        str [i] = pSTR [*pPOS];
        ++*pPOS;
        ++i;
    }
    
    str [i] = '\0';
    memcpy(val_s, str, strlen(str));
    
    Cell_t* cell_new = CellNew(Tree);
    cell_new->data = val_s;
    
    Space (pSTR, pPOS);
    
    return cell_new;
}



Cell_t* Creat_Cell (Tree_t* Tree, Cell_t* cell1, Cell_t* cell2, Cell_t* cell3, char* str) {
    assert(Tree);
    assert(str);
    
    cell3 = CellNew (Tree);
    cell3->data = str;
    cell3->nextl = cell1;
    cell3->nextr = cell2;
    cell3->nextl->prev = cell3;
    cell3->nextr->prev = cell3;
    
    return cell3;
}
