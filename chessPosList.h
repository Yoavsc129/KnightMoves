#ifndef _CHESS_POS_LIST
#define _CHESS_POS_LIST

#include "general.h"
#include "chessPosarr.h"
#include "pathTree.h"


typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
}chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
}chessPosList;


void makeEmptyList(chessPosList* lst);
int isEmptyList(chessPosList lst);
void insertDataToEndList(chessPosList* lst, chessPos data);
void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail);
void insertDataToStartList(chessPosList* lst, chessPos data);
void insertNodeToStartList(chessPosList* lst, chessPosCell* newTail);
chessPosCell* createNewListNode(chessPos data, chessPosCell* next);
void removeNode(chessPosCell* after);
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void findKnightPathCoveringAllBoardRec(treeNode* root, chessPosList* res, int counter, bool* fullPath);
void display(chessPosList* lst);
void freeList(chessPosList* lst);


#endif // !_CHESS_POS_LIST


