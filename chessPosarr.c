
/*****************************************chessPosarr***************************************
*chessposarray functions.
*************************************************************************************/
#include "chessPosarr.h"

//Creates a 2 dimensional array. Each cell contains an array of all the possible moves from that cell.
chessPosArray*** validKnightMoves() {
	int i, j;

	//build 2-dim array
	chessPosArray*** board = NULL;
	board = newBoard(board, BOARD_SIZE);
	

	

	//run on every cell in the "board"
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			addKnightMoveFromSpot(i, j, board);

	
	return board;
}

//The function gets a board and a row and col and updates cells value around that position in the corresponding places.
void addKnightMoveFromSpot(int row, int col, chessPosArray*** board) {
	int i, j, counter = 0;

	for (i = row - 2; i <= row + 2; i++)
		if (i != row && i >= 0 && i < BOARD_SIZE)
			for (j = col - 2; j <= col + 2; j = j++)
				if (j != col && j >= 0 && j < BOARD_SIZE)
					if (row - i != col - j && row - i != (col - j) * -1)
						board = addKnightLocation(board, row, col, i, j);
}

//The function adds current location (krow, kcol) to position array.
chessPosArray*** addKnightLocation(chessPosArray*** board, int krow, int kcol, int row, int col) {
	int positionIndex;
	board[krow][kcol]->size++;
	positionIndex = board[krow][kcol]->size - 1;

	board[krow][kcol]->position = (chessPos*)realloc(board[krow][kcol]->position, board[krow][kcol]->size * sizeof(chessPos));
	checkMemoryAllocation(board[krow][kcol]->position);

	board[krow][kcol]->position[positionIndex][0] = 'A' + row; //to get letters A-H
	board[krow][kcol]->position[positionIndex][1] = (char)('0' + (col + 1));


	return board;
}

//The function builds a new board.
chessPosArray*** newBoard(chessPosArray*** board, int size) {
	int i, j;

	board = (chessPosArray***)malloc(size * sizeof(chessPosArray**));
	checkMemoryAllocation(board);

	for (i = 0; i < size; i++) {
		board[i] = (chessPosArray**)malloc(size * sizeof(chessPosArray*));
		checkMemoryAllocation(board[i]);

		for (j = 0; j < size; j++) {
			board[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
			board[i][j]->size = 0;
			board[i][j]->position = (chessPos*)malloc(sizeof(chessPos));
			checkMemoryAllocation(board[i][j]->position);
		}
	}
	return board;
}

//The function frees a board
void freeAll(chessPosArray*** board, int size) {
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			free(board[i][j]->position);
			free(board[i][j]);
		}
		free(board[i]);
	}
	free(board);
}