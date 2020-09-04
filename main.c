#include "board.h"
#include <stdio.h>
int main()
{
	board newBoard;
	createBoard(&newBoard);
	initRandBoard(&newBoard);
	printBoard(&newBoard);
}
