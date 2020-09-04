#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 10

#define LARGEST_SHIP 4

/*Debugging tools*/
void printBoard(board playersBoard) {
	for (int row = 0; row < playersBoard.height; ++row) {
		for (int col = 0; col < playersBoard.width; ++col)
			printf("%d ", playersBoard.board[row][col]);
		printf("\n");
	}
			
}
/******************/

board createBoard() {
	board newBoard;
	
	newBoard.width = WIDTH;
	newBoard.height = HEIGHT;
	
	newBoard.board = (cell**) calloc(HEIGHT, sizeof(cell*));
	//Need to add ERROR if calloc failed
	
	for (int row = 0; row < WIDTH; ++row) {
		newBoard.board[row] = (cell*) calloc(WIDTH, sizeof (cell));
		//Need to add ERROR if calloc failed, and free all alocated memory up to this point
	}
	
	return newBoard;
}

void initRandBoard(board* playersBoard) {
	int i,j;
	
	for (i = 0; i < LARGEST_SHIP; ++i) {
		for( j = 0; j <=i; ++j)
			initRandShip(playersBoard, LARGEST_SHIP - i);
	}
}

void initRandShip(board* playersBoard, unsigned char shipSize) {
	unsigned char row, col, dir;
	
	unsigned char searchPlacement = 1;
	unsigned char dirChange;
	unsigned char i;
	
	srand(time(NULL));
	
	while (searchPlacement) {
		row = rand() % 10;
		col = rand() % 10;
		dir = rand() % 4;
		
		if ((*playersBoard).board[row][col] != emptyCell)
			continue;
		
		dirChange = 0;
		
		while (dirChange < 3) {
			if (0 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (row - i < 0 || (*playersBoard).board[row - i][col] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*playersBoard).board[row - i][col] = shipCell;
						addShipPerimeter(playersBoard, row - i, col);
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (1 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (col + i >  WIDTH - 1 ||
						(*playersBoard).board[row][col + i] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*playersBoard).board[row][col + i] = shipCell;
						addShipPerimeter(playersBoard, row, col + i);
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (2 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (row + i >  HEIGHT - 1 ||
						(*playersBoard).board[row + i][col] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*playersBoard).board[row + i][col] = shipCell;
						addShipPerimeter(playersBoard, row + i, col);
					}
					searchPlacement = 0;
					break;
				}
			}
			
			if (3 == dir) {
				for (i = 1; i < shipSize; ++i) {
					if (col - i < 0 || (*playersBoard).board[row][col - i] != emptyCell) {
						dir = (dir + 1) % 4;
						dirChange++;
						break;
					}
				}
				if (shipSize == i) {
					for (i = 0; i < shipSize; ++i) {
						(*playersBoard).board[row][col - i] = shipCell;
						addShipPerimeter(playersBoard, row, col - i);
					}
					searchPlacement = 0;
					break;
				}
			}
		}
	}
}

void addShipPerimeter(board* playersBoard, unsigned char row, unsigned char col) {
	int i, j;
	
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			if (row + i < 0 || row + i > WIDTH - 1 || col + j < 0 || col + j > HEIGHT - 1 ||
				(*playersBoard).board[row + i][col + j] == shipCell)
				continue;
			
			(*playersBoard).board[row + i][col + j] = shipPerimeterCell;
		}
	}
}















