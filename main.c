#include "board.h"
#include <stdio.h>
int main()
{
	board firstPlayersBoard = createBoard();
	//printBoard(firstPlayersBoard);
	initRandBoard(&firstPlayersBoard);
	printBoard(firstPlayersBoard);
}
