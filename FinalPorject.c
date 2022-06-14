/*****************************************Final Project***************************************
* This is the main class of the final project.
* 
* it will run all parts (1-7) in order.
**********************************************************************************************/
#include "FinalProject.h"

void main() {
	
	runMenu();
}

//runs part 7
void runMenu() {
	int input;
	char row, col;
	chessPos position = { '0', '0' };
	pathTree tr;
	chessPosList* lst = NULL;

	tr.root = NULL;

	while (1) {
		printf("Enter a number (1-6)\n 1. Enter a knight's starting position\n 2. Crete all possible knight paths\n 3. Find a knight path covering all board\n 4. Save a knight path covering all board to file\n 5. Load and display path from file\n 6. Exit\n");

		scanf("%d", &input);
		getchar();

		switch (input) {
		case 1:
			enterPositon(&row, &col);
			position[0] = row;
			position[1] = col;
			break;
		case 2:
			if (position[0] == '0')
				printf("Please enter positions in option 1.\n");
			else {
				if (tr.root != NULL)
					freeTree(&tr);
				tr = runOption2(&position);
			}
			break;
		case 3:
			if (position[0] == '0')
				printf("Please enter positions in option 1.\n");
			else {
				if (lst != NULL)
					if (!isEmptyList(*lst))
						freeList(lst);
				lst = runOption3(&position, &tr);
			}
			break;
		case 4:
			if (position[0] == '0')
				printf("Please enter positions in option 1.\n");
			else
				runOption4(&tr, lst, &position);
			break;
		case 5:
			runOption5();
			break;
		case 6:
			printf("Thanks for playing!");
			if (lst)
				freeList(lst);
			if (tr.root)
				freeTree(&tr);
			exit(1);
			break;
		default:
			printf("Invalid input. enter a number between 1-6\n");
			break;

		}
	}
}

//runs part 2
chessPosList createList() {
	chessPosList lst; 
	makeEmptyList(&lst);

	chessPos curr = { 'A','1' };
	insertDataToEndList(&lst, curr);

	curr[0] = 'B';
	curr[1] = '2';
	insertDataToEndList(&lst, curr);

	curr[0] = 'A';
	curr[1] = '1';
	insertDataToEndList(&lst, curr);

	curr[0] = 'C';
	curr[1] = '3';
	insertDataToEndList(&lst, curr);

	return lst;
}

//gets a starting position of the knight from the user until it is valid
void enterPositon(char* row, char* col) {
	bool run = true;
	system("cls");
	printf("\nEnter Knight's starting position: ");
	

	while (run) {
		scanf("%c%c", row, col);

		if ((*row >= 'A' && *row <= 'E' && *col >= '1' && *col <= '5')) {
			run = false;
		}
		else
			printf("Invalid input: Enter a position between A-E and 1-5\n");
	}
	getchar();
}

//creates all possible knight paths in a tree, and returns the tree
pathTree runOption2(chessPos* position) {
	system("cls");
	pathTree tr = findAllpossibleknightpaths(position);

	return tr;
}

//finds a knight path that covers the whole board (if there is one)
chessPosList* runOption3(chessPos* position, pathTree* tr) {
	chessPosList* lst = NULL;
	system("cls");
	if (tr->root == NULL) {
		*tr = runOption2(position);
	}

	lst = findKnightPathCoveringAllBoard(tr);

	if (lst->head == NULL){
		free(lst);
		lst = NULL;
		printf("Path not found, please enter a different starting position.\n");
	}


	return lst;
}

//saves the path from runOption3 in a bin file of the users choosing
void runOption4(pathTree* tr, chessPosList* lst, chessPos* position) {
	system("cls");
	if (lst == NULL) 
		lst = runOption3(position, tr);
	
	if (lst == NULL)
		return;
	

	char* file_name;
	
	printf("Enter file name to save list in binary file (.bin): ");
	file_name = getfilename();

	saveListToBinFile(file_name, lst);
	free(file_name);
}

//loads and displays path that was saved in a file of the users choosing.
void runOption5() {
	system("cls");
	char* file_name;
	printf("Enter file name to open binary file of list: ");
	file_name = getfilename();

	int check = checkAndDisplayPathFromFile(file_name);

	switch (check) {
	case -1:
		printf("File not found!\n");
		break;
	case 1:
		printf("Invalid path of knight!\n");
		break;
	case 2: 
		printf("Path covers the entire board!\n\n");
		break;
	case 3:
		printf("Path did not cover entire board.\n\n");
		break;
	}

	free(file_name);
}