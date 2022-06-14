
/*****************************************ChessPosList***************************************
*chessposlist functions.
*************************************************************************************/

#include "chessPosList.h"

//This function makes the list empty.
void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

//This function checks if a list is empty.
int isEmptyList(chessPosList lst)
{
	return (lst.head == NULL);
}

//This function gets a list and a char and adds a new node with the char to the list.
void insertDataToEndList(chessPosList* lst, chessPos data)
{
	chessPosCell* result = createNewListNode(data, NULL);

	insertNodeToEndList(lst, result);
}

//This function gets a list and a node and adds the node to the end of the list.
void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail)
{
	newTail->next = NULL;

	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

//This function gets a list and data and adds the data as a ndoe to the begining of the list.
void insertDataToStartList(chessPosList* lst, chessPos data) {
	chessPosCell* result = createNewListNode(data, NULL);

	insertNodeToStartList(lst, result);
}

//This function gets a list and a node and adds the node to the begining of the list.
void insertNodeToStartList(chessPosList* lst, chessPosCell* newHead) {
	if (isEmptyList(*lst))
		lst->head = lst->tail = newHead;
	else {
		newHead->next = lst->head;
		lst->head = newHead;
	}
}

//This function gets a position and creates a new listNode with the position.
chessPosCell* createNewListNode(chessPos data, chessPosCell* next)
{
	chessPosCell* res;

	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkMemoryAllocation(res);
	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next = next;

	return res;

}

//This function removes a node from a list.
void removeNode(chessPosCell* after)
{
	chessPosCell* toDelete;

	toDelete = after->next;
	after->next = toDelete->next;
	free(toDelete);
}

//The function gets a tree and finds a path in the tree that the knight covers the whole board, if there is one.
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
	chessPosList* res = (chessPosList*)malloc(sizeof(chessPosList));
	checkMemoryAllocation(res);
	makeEmptyList(res);
	bool fullPath = false;
	findKnightPathCoveringAllBoardRec(path_tree->root, res, 1, &fullPath);
	return res;
}

//reccursive function of 'findKnightPathCoveringAllBoard'.
void findKnightPathCoveringAllBoardRec(treeNode* root, chessPosList* res, int counter, bool* fullPath) {
	if (root->next_possible_positions == NULL) {
		if (counter == MAX_LENGTH(BOARD_SIZE)) {
			*fullPath = true;
			insertDataToStartList(res, root->position);
		}
		return;
	}

	treeNodeListCell* listNode = root->next_possible_positions;

	while (listNode != NULL && *fullPath == false) {
		findKnightPathCoveringAllBoardRec(listNode->node, res, counter + 1, fullPath);
		listNode = listNode->next;
	}

	if (*fullPath == true) {
		insertDataToStartList(res, root->position);
	}
}

//This function gets a list and prints it on the screen.
void display(chessPosList* lst) {
	//build array for comparison + format to '0'

	chessPosCell* curr = lst->head, * temp = NULL;
	int board[BOARD_SIZE][BOARD_SIZE];
	initboard(board);
	int pos[2];
	int i = 1;
	while (curr != NULL) {

		pos[0] = (int)(curr->position[0] - 'A');
		pos[1] = (int)(curr->position[1] - '1');
		if (board[pos[0]][pos[1]] > 0) {
			if (lst->tail == curr)
				lst->tail = temp;
			curr = curr->next;
			removeNode(temp);
		}
		else {
			board[pos[0]][pos[1]] = i;
			i++;
			temp = curr;
			curr = curr->next;
		}

	}
	printBoard1(board);
}

//This function frees a list.
void freeList(chessPosList* lst)
{
	chessPosCell* curr = lst->head, * next;

	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}


