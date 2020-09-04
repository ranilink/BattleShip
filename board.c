#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* rand */

#define BOARD_SIZE 10

#define LARGEST_SHIP 4

#define FALSE 0
#define TRUE 1

err_t initRandShip(board_t* board, int shipSize);

int checkDir(board_t* board,int row, int col, dir_t dir, int shipSize);

void buildShip(board_t* board, int row, int col, dir_t dir, int shipSize);

void addPerimeter(board_t* board, int row, int col);

/* Debugging tools */
void printBoard(board_t* board) {
	for (int row = 0; row < BOARD_SIZE; ++row) {
		for (int col = 0; col < BOARD_SIZE; ++col)
			printf("%d ", board->m_grid[row][col]);
		printf("\n");
	}
}
/******************/

board_t* createBoard() {

	board_t* newBoard = (board_t*) malloc(sizeof(board_t));
	if (NULL == newBoard)
		return NULL;
	
	newBoard->m_grid = (cell_t**) malloc(BOARD_SIZE * sizeof(cell_t*));
	if (NULL == newBoard->m_grid) {
		free(newBoard);
		return NULL;
	}
	
	for (int row = 0; row < BOARD_SIZE; ++row) {
		newBoard->m_grid[row] = (cell_t*) calloc(BOARD_SIZE, sizeof(cell_t));
		if (NULL == newBoard->m_grid[row]) {
			for (int i = 0; i < row; ++i)
				free(newBoard->m_grid[i]);
			
			free(newBoard->m_grid);
			free(newBoard);
			return NULL;
		}
	}
	
	return newBoard;
}

void destroyBoard(board_t** board) {
	if (NULL == board || NULL == *board)
		return;
	
	if (NULL != (*board)->m_grid) {
		for (int row = 0; row < BOARD_SIZE; ++row)
				free((*board)->m_grid[row]);
		free((*board)->m_grid);
	}
	
	free(*board);
	*board = NULL;
}

err_t initRandBoard(board_t* board) {

	if (NULL == board || NULL == board->m_grid)
		return INVALID_INPUT;
	
	for (int i = 0; i < LARGEST_SHIP; ++i) {
		for (int j = 0; j <= i; ++j)
			initRandShip(board, LARGEST_SHIP - i);
	}
	
	return SUCCESS;
}

err_t initRandShip(board_t* board, int shipSize) {
	int row, col, dir;
	
	int searchPlacement = TRUE;
	int dirChange;
	
	if (NULL == board || NULL == board->m_grid || shipSize < 1 || shipSize > LARGEST_SHIP)
		return INVALID_INPUT;
	
	srand(time(NULL));
	
	while (searchPlacement) {
		row = rand() % 10;
		col = rand() % 10;
		dir = rand() % 4;
		
		if (board->m_grid[row][col] != EMPTY_CELL)
			continue;
		
		dirChange = 0;
		
		while (dirChange < 3) {
			if (FALSE == checkDir(board, row, col, dir, shipSize)) {
				dir = (dir + 1) % 4;
				dirChange++;
				continue;
			}
			
			buildShip(board, row, col, dir, shipSize);
			searchPlacement = 0;
			break;
		}
	}
	
	return SUCCESS;
}

int checkDir(board_t* board,int row, int col, dir_t dir, int shipSize) {
	switch (dir)
	{
		case UP:
			for (int i = 1; i < shipSize; ++i) {
				if (row - i < 0 || board->m_grid[row - i][col] != EMPTY_CELL)
					return FALSE;
			}
			break;
		
		case RIGHT:
			for (int i = 1; i < shipSize; ++i) {
				if (col + i >  BOARD_SIZE - 1 ||
					board->m_grid[row][col + i] != EMPTY_CELL)
					return FALSE;
			}
			break;
		
		case DOWN:
			for (int i = 1; i < shipSize; ++i) {
				if (row + i >  BOARD_SIZE - 1 ||
					board->m_grid[row + i][col] != EMPTY_CELL)
					return FALSE;
			}
			break;
		
		case LEFT:
			for (int i = 1; i < shipSize; ++i) {
				if (col - i < 0 || board->m_grid[row][col - i] != EMPTY_CELL)
					return FALSE;
			}
			break;
	}
	
	return TRUE;
}

void buildShip(board_t* board, int row, int col, dir_t dir, int shipSize) {
	switch (dir)
	{
		case UP:
			for (int i = 0; i < shipSize; ++i) {
				board->m_grid[row - i][col] = SHIP_CELL;
				addPerimeter(board, row - i, col);
			}
			break;
		
		case RIGHT:
			for (int i = 0; i < shipSize; ++i) {
				board->m_grid[row][col + i] = SHIP_CELL;
				addPerimeter(board, row, col + i);
			}
			break;
		
		case DOWN:
			for (int i = 0; i < shipSize; ++i) {
				board->m_grid[row + i][col] = SHIP_CELL;
				addPerimeter(board, row + i, col);
			}
			break;
		
		case LEFT:
			for (int i = 0; i < shipSize; ++i) {
				board->m_grid[row][col - i] = SHIP_CELL;
				addPerimeter(board, row, col - i);
			}
			break;
	}
}

void addPerimeter(board_t* board, int row, int col) {
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (row + i < 0 || row + i > BOARD_SIZE - 1 ||
				col + j < 0 || col + j > BOARD_SIZE - 1 ||
				board->m_grid[row + i][col + j] == SHIP_CELL)
				continue;
			
			board->m_grid[row + i][col + j] = SHIP_PERIMETER_CELL;
		}
	}
}















