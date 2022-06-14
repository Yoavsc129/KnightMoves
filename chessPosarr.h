#ifndef _CHESS_POS_ARR_H
#define _CHESS_POS_ARR_H
#include "general.h"

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* position;
}chessPosArray;

chessPosArray*** validKnightMoves();
void addKnightMoveFromSpot(int row, int col, chessPosArray*** board);
chessPosArray*** addKnightLocation(chessPosArray*** board, int krow, int kcol, int row, int col);
chessPosArray*** newBoard(chessPosArray*** board, int size);
void freeAll(chessPosArray*** board, int size);

#endif // !_CHESS_POS_ARR_H


