#include "board.h"
#include <stdio.h>
int main()
{
	board_t* newBoard = createBoard();
	printBoard(newBoard);
	initRandBoard(newBoard);
	printBoard(newBoard);
	destroyBoard(&newBoard);
	printf("%p\n", newBoard);
}
