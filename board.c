#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 10

#define LARGEST_SHIP 4

/*Debugging tools*/
void printBoard(board* playersBoard) {
	for (int row = 0; row < (*playersBoard).height; ++row) {
		for (int col = 0; col < (*playersBoard).width; ++col)
			printf("%d ", (*playersBoard).board[row][col]);
		printf("\n");
	}
			
}
/******************/

Err createBoard(board* newBoard) {
	if (NULL == newBoard)
		return INVALID_INPUT;
	
	(*newBoard).width = WIDTH;
	(*newBoard).height = HEIGHT;
	
	(*newBoard).board = (cell**) calloc(HEIGHT, sizeof(cell*));
	if (NULL == (*newBoard).board)
		return ALLOCATION_FAIL;
	
	for (int row = 0; row < WIDTH; ++row) {
		(*newBoard).board[row] = (cell*) calloc(WIDTH, sizeof (cell));
		if (NULL == (*newBoard).board[row]) {
			for (int i = 0; i < row; ++i)
				free((*newBoard).board[i]);
			free((*newBoard).board);
			return ALLOCATION_FAIL;
		}
	}
	
	return SUCCESS;
}

Err initRandBoard(board* newBoard) {
	int i,j;
	
	if (NULL == newBoard)
		return INVALID_INPUT;
	
	for (i = 0; i < LARGEST_SHIP; ++i) {
		for( j = 0; j <=i; ++j)
			initRandShip(newBoard, LARGEST_SHIP - i);
	}
	
	return SUCCESS;
}

Err initRandShip(board* newBoard, unsigned char shipSize) {
	unsigned char row, col, dir;
	
	unsigned char searchPlacement = 1;
	unsigned char dirChange;
	unsigned char i;
	
	if (NULL == newBoard || shipSize < 1)
		return INVALID_INPUT;
	
	srand(time(NULL));
	
	while (searchPlacement) {
		row = rand() % 10;
		col = rand() % 10;
		dir = rand() % 4;
		
		if ((*newBoard).board[row][col] != emptyCell)
			continue;
		
		dirChange = 0;
		
		while (dirChange < 3) {
			if (0 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (row - i < 0 || (*newBoard).board[row - i][col] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*newBoard).board[row - i][col] = shipCell;
						 if (addShipPerimeter(newBoard, row - i, col) == INVALID_INPUT)
						 	return INVALID_INPUT;
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (1 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (col + i >  WIDTH - 1 ||
						(*newBoard).board[row][col + i] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*newBoard).board[row][col + i] = shipCell;
						if (addShipPerimeter(newBoard, row, col + i) == INVALID_INPUT)
							return INVALID_INPUT;
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (2 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (row + i >  HEIGHT - 1 ||
						(*newBoard).board[row + i][col] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*newBoard).board[row + i][col] = shipCell;
						if (addShipPerimeter(newBoard, row + i, col) == INVALID_INPUT)
							return INVALID_INPUT;
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (3 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (col - i < 0 || (*newBoard).board[row][col - i] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*newBoard).board[row][col - i] = shipCell;
						if (addShipPerimeter(newBoard, row, col - i) == INVALID_INPUT)
							return INVALID_INPUT;
					}
					searchPlacement = 0;
					break;
				}
			}
		}
	}
	
	return SUCCESS;
}

Err addShipPerimeter(board* newBoard, unsigned char row, unsigned char col) {
	int i, j;
	
	if (NULL == newBoard)
		return INVALID_INPUT;
	
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			if (row + i < 0 || row + i > WIDTH - 1 || col + j < 0 || col + j > HEIGHT - 1 ||
				(*newBoard).board[row + i][col + j] == shipCell)
				continue;
			
			(*newBoard).board[row + i][col + j] = shipPerimeterCell;
		}
	}
	
	return SUCCESS;
}















