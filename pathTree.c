
/*****************************************pathTree***************************************
* all fuctions of pathTree 
*****************************************************************************************/

#include "pathTree.h"

//will build a tree that has all the possible paths a knight can go from one spot without repeating the spots in that path.  
pathTree findAllpossibleknightpaths(chessPos* startingposition)
{
	chessPosArray*** board = validKnightMoves();
	int arr[BOARD_SIZE][BOARD_SIZE];
	initboard(arr);
	pathTree res;
	res.root = findAllpossibleknightpathsRec(startingposition, board, arr);
	freeAll(board, BOARD_SIZE);
	return res;
}

//reccursive function for 'findAllpossibleknightpaths'
treeNode* findAllpossibleknightpathsRec(chessPos* position, chessPosArray*** board, int countboard[][BOARD_SIZE])
{

	treeNode* res = createNewtreeNode(position);
	int i;
	int posA, pos1;
	int curposA = position[0][0] - 'A', curpos1 = position[0][1] - '1';
	int size = board[curposA][curpos1]->size;
	countboard[curposA][curpos1] = 1;
	for (i = size - 1; i >= 0; i--) {
		posA = board[position[0][0] - 'A'][position[0][1] - '1']->position[i][0] - 'A';
		pos1 = board[position[0][0] - 'A'][position[0][1] - '1']->position[i][1] - '1';
		if (countboard[posA][pos1] == 0) {
			insertdatatotreeNodeList(res);
			res->next_possible_positions->node = findAllpossibleknightpathsRec(board[curposA][curpos1]->position[i], board, countboard);
		}
	}
	countboard[curposA][curpos1] = 0;
	return res;
}

//creats a new treeNode with its data being the position that it was given.
treeNode* createNewtreeNode(chessPos* position)
{
	treeNode* res = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(res);
	res->position[0] = position[0][0];
	res->position[1] = position[0][1];
	res->next_possible_positions = NULL;

	return res;
}

//checks if the treeNode is empty
int isEmptytreenodelist(treeNode* node)
{
	return (node->next_possible_positions == NULL);
}

//creats a new empty treeNodeList cell
treeNodeListCell* createNewtreeNodelistCell()
{
	treeNodeListCell* res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(res);
	res->next = NULL;

	return res;
}

//creates new treeNodeList cell with the data from treeNode
void insertdatatotreeNodeList(treeNode* node)
{
	treeNodeListCell* newhead;
	newhead = createNewtreeNodelistCell();
	insertnodetotreeNodeList(node, newhead);
}

//adds the treeNodeList cell to the treeNodeList
void insertnodetotreeNodeList(treeNode* node, treeNodeListCell* newhead)
{
	if (isEmptytreenodelist(node)) {
		node->next_possible_positions = newhead;
	}
	else {
		newhead->next = node->next_possible_positions;
		node->next_possible_positions = newhead;
	}
}

// frees the memory of a tree
void freeTree(pathTree* tr)
{
	freetreelist(tr->root);
	free(tr->root);
}

//frees the memory of a list
void freetreelist(treeNode* node)
{
	if (node->next_possible_positions == NULL)
		return;

	treeNodeListCell* curr = node->next_possible_positions, * next;
	while (curr != NULL) {
		next = curr->next;
		freetreelist(curr->node);
		free(curr->node);
		free(curr);
		curr = next;
	}
}
