#ifndef _PATH_TREE_H
#define _PATH_TREE_H

#include "general.h"
#include "chessPosarr.h"

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
}pathTree;

pathTree findAllpossibleknightpaths(chessPos* startingposition);
treeNode* findAllpossibleknightpathsRec(chessPos* position, chessPosArray*** board, int countboard[][BOARD_SIZE]);
treeNode* createNewtreeNode(chessPos* position);
int isEmptytreenodelist(treeNode* node);
treeNodeListCell* createNewtreeNodelistCell();
void insertdatatotreeNodeList(treeNode* node);
void insertnodetotreeNodeList(treeNode* node, treeNodeListCell* newhead);
void freeTree(pathTree* tr);
void freetreelist(treeNode* node);

#endif // !_PATH_TREE_H

