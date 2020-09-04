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
void printBoard(board playersBoard);
/******************/

board createBoard();

void initRandBoard(board* playerBoard);

void initRandShip(board* playersBoard, unsigned char shipSize);

void addShipPerimeter(board* playersBoard, unsigned char row, unsigned char col);
