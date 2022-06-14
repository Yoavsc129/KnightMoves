#ifndef _FINAL_PROJECT_H
#define _FINAL_PROJECT_H
#include "general.h"
#include "chessPosarr.h"
#include "chessPosList.h"
#include "pathTree.h"
#include "file.h"


void runMenu();
chessPosList createList();
void enterPositon(char* row, char* col);
pathTree runOption2(chessPos* position);
chessPosList* runOption3(chessPos* position, pathTree* tr);
void runOption4(pathTree* tr, chessPosList* lst, chessPos* position);
void runOption5();
#endif // !_FINAL_PROJECT_H

