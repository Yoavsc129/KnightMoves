/*****************************************File***************************************
*functions for creating and opening files with path lists.
*************************************************************************************/

#include "file.h"

//saves a list of knight positions to a bin file.
void saveListToBinFile(char* file_Name, chessPosList* pos_List) {
	FILE* f;
	f = fopen(file_Name, "wb");

	short int nPositions = 0;
	chessPosCell* curr = pos_List->head;
	char bitstr[SIZE_OF_BYTE];
	int currIndex = 0;
	int strindex = 0;
	int physize = 1;
	char currpos;
	BYTE* bitOfChar = (BYTE*)malloc(physize * sizeof(BYTE));
	while (curr != NULL) {
		nPositions++;
		currpos = curr->position[0] - 'A';
		createBinStr(currpos, bitstr, &bitOfChar, &strindex, &currIndex, &physize);
		currpos = curr->position[1] - '1';
		createBinStr(currpos, bitstr, &bitOfChar, &strindex, &currIndex, &physize);
		curr = curr->next;
	}
	if (strindex != 0)
		finishbyte(&bitOfChar, &currIndex, physize, bitstr, strindex);

	writeToFile(f, bitOfChar, currIndex, nPositions);
	fclose(f);
	free(bitOfChar);
}

//creates a byte from a string of 0's and 1's
BYTE createByte(char* str) {
	BYTE res = 0;
	int i;
	for (i = 0; i < SIZE_OF_BYTE; i++) {
		res = res << 1;
		res += (str[i] == '1' ? 1 : 0);
	}
	return res;
}

//creates a string of 0's and 1's representing a binary value
void createBinStr(char position, char* str, BYTE** bytearr, int* strindex, int* byteindex, int* physize)//pay attention
{
	int i, mask;
	for (i = 2; i >= 0; i--) {
		if ((*byteindex) == (*physize)) {
			(*physize) *= 2;
			*bytearr = (BYTE*)realloc((*bytearr), (*physize) * sizeof(BYTE));
		}
		mask = 1 << i;
		str[*strindex] = ((position & mask) ? '1' : '0');
		(*strindex)++;
		if (*strindex == SIZE_OF_BYTE) {
			bytearr[0][*byteindex] = createByte(str);
			(*byteindex)++;
			(*strindex) = 0;
		}
	}
}
//Adds zeros to the end of the string to finish the last byte.
void finishbyte(BYTE** bytearr, int* currindex, int physize, char* bitstr, int strindex) {

	if ((*currindex) == (physize)) {
		physize *= 2;
		*bytearr = (BYTE*)realloc((*bytearr), physize * sizeof(BYTE));
	}
	while (strindex < 8) {
		bitstr[strindex] = '0';		
		strindex++;
	}

	bytearr[0][*currindex] = createByte(bitstr);
	(*currindex)++;


	*bytearr = (BYTE*)realloc((*bytearr), (*currindex) * sizeof(BYTE));
}
//saves the bit value of a char into a file
void writeToFile(FILE* f, char* bitOfChar, int sizeOfBitChar, short int nPositions) {
	int i;
	fwrite(&nPositions, sizeof(short int), 1, f);

	/*for (i = 0; i < sizeOfBitChar; i++)
		fwrite(&bitOfChar[i], sizeof(char), 1, f);*/
	fwrite(bitOfChar, sizeof(BYTE), sizeOfBitChar, f);
}
//checks that the binary file has a valid knight path and prints out the path 
int checkAndDisplayPathFromFile(char* file_name) {
	FILE* f = fopen(file_name, "rb");
	if (checkFile(f) == 0) {
		return -1;
	}

	short int numOfPos;
	int check, count = 0;
	fread(&numOfPos, sizeof(short int), 1, f);

	int sizeOfArr = getSize(numOfPos);
	BYTE* arr = getByte(f, sizeOfArr);

	char* str = toString(arr, sizeOfArr);

	chessPosList lst;
	check = createListFromFile(&lst, str, numOfPos, &count);
	if (check == 2 || check == 3) {
		display(&lst);
	}

	fclose(f);
	return check;
}

//creates a list of knight positions from a binary file
int createListFromFile(chessPosList* lst, char* str, int numOfPos, int* count) {
	makeEmptyList(lst);

	int i, j = 0, check = 1;
	chessPos position;
	int arr[BOARD_SIZE][BOARD_SIZE] = { 0 };
	for (i = 0; i < numOfPos && check == 1; i++) {
		position[0] = getPos(str + j) + 'A';
		j += 3;
		position[1] = getPos(str + j) + '1';
		j += 3;

		if (arr[position[0] - 'A'][position[1] - '1'] == 0) {
			arr[position[0] - 'A'][position[1] - '1'] = 1;
			(*count)++;
		}

		if (i != 0) {
			if (!checkIfValidPosition(lst->tail->position, position))
				return 1;
		}

		insertDataToEndList(lst, position);
	}
	if ((*count) == (MAX_LENGTH(BOARD_SIZE)))
		return 2;
	else
		return 3;
}


//stores a byte from a binary file to an array 
BYTE* getByte(FILE* f, int size) {
	int i;

	BYTE* arr = (BYTE*)malloc(size * sizeof(BYTE));
	checkMemoryAllocation(arr);

	/*for (i = 0; i < size; i++)
		check = fread(&arr[i], sizeof(BYTE), 1, f);*/
	fread(arr, sizeof(BYTE), size, f);
	return arr;
}

//gets total amount of bytes we will need according to the number of positions
int getSize(int numOfPos) {
	int size;

	size = numOfPos * 6;

	while (size % 8 != 0)
		size++;

	return size / 8;
}
//turns from a byte to a binary string
char* toString(BYTE* arr, int size) {
	int i, j, index = 0;
	BYTE mask;

	char* str = (char*)malloc((size * 8) * sizeof(char));
	checkMemoryAllocation(str);

	for (i = 0; i < size; i++)
		for (j = SIZE_OF_BYTE - 1; j >= 0; j--) {
			mask = 1 << j;
			str[index] = ((arr[i] & mask) ? '1' : '0');
			index++;
		}

	return str;
}
//checks if next is a valid positon for a knight to get to from position
int checkIfValidPosition(chessPos position, chessPos next) {
	int i, j;
	int row = position[0] - 'A';
	int col = position[1] - '1';
	int rowNext = next[0] - 'A';
	int colNext = next[1] - '1';

	for (i = row - 2; i <= row + 2; i++)
		if (i != row && i >= 0 && i < BOARD_SIZE)
			for (j = col - 2; j <= col + 2; j = j++)
				if (j != col && j >= 0 && j < BOARD_SIZE)
					if (row - i != col - j && row - i != (col - j) * -1)
						if (i == rowNext && j == colNext)
							return 1;

	return 0;
}


//gets position in binary
char getPos(char* str) {
	char pos = 0;

	int i;

	for (i = 0; i < 3; i++) {
		pos = pos << 1;
		pos += (str[i] == '1' ? 1 : 0);
	}

	return pos;
}
//creates a dynamic string for the file name.
char* getfilename()
{
	int logSize = 0, phySize = 1;
	char c;
	char* res = (char*)malloc(phySize * sizeof(char));
	checkMemoryAllocation(res);
	c = getchar();

	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			res = (char*)realloc(res, sizeof(char) * phySize);
		}

		res[logSize] = c;
		logSize++;
		c = getchar();
	}

	res = (char*)realloc(res, sizeof(char) * (logSize + 1));
	res[logSize] = '\0';
	return res;
}

//checks if file opened successfully
int checkFile(FILE* f)
{
	if (f == NULL)
		return 0;
	return 1;
}