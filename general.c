/*****************************************General***************************************
* general functions.
****************************************************************************************/

#include "general.h"

//sets board to be of value 0 in all spots.
void initboard(int board[][BOARD_SIZE])
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = 0;
}

//prints line of numbers according to board size.
void printNumLine(int col) {
	int i = 1;

	printf("|    |");
	while (i <= col) {
		printf("%3d |", i);
		i++;
	}
	printf("\n");
}

//prints lineof dashes according to board size.
void printDashLine(int row) {
	int i;

	printf("+");
	for (i = 0; i <= row; i++)
		printf("----+");
	printf("\n");

}
//prints a board
void printBoard1(int gameboard[][BOARD_SIZE])
{
	int i, j;
	char place = 'A';

	printDashLine(BOARD_SIZE);
	printNumLine(BOARD_SIZE);
	for (i = 0; i < BOARD_SIZE; i++) {
		printDashLine(BOARD_SIZE);
		printf("|  %c |", place);
		place++;
		for (j = 0; j < BOARD_SIZE; j++) {
			printf("%3d |", gameboard[i][j]);
		}
		printf("\n");
	}
	printDashLine(BOARD_SIZE);
}

//checks if memory of pointers and dynamic arrays exist
void checkMemoryAllocation(void* ptr) {
	if (ptr == NULL) {
		printf("Memory allocation failed!\n");
		exit(1);
	}
}
