typedef enum
{
	SUCCESS,
	INVALID_INPUT,
	ALLOCATION_FAIL
} Err;

typedef enum
{
	emptyCell,
	shipCell,
	shipPerimeterCell
} cell;

typedef struct
{
	unsigned char width;
	unsigned char height;
	cell** board;
} board;

/*Debugging tools*/
void printBoard(board* playersBoard);
/******************/

Err createBoard(board* newBoard);

Err initRandBoard(board* newBoard);

Err initRandShip(board* newBoard, unsigned char shipSize);

Err addShipPerimeter(board* newBoard, unsigned char row, unsigned char col);
