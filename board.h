typedef enum
{
	SUCCESS = 0,
	INVALID_INPUT = 1,
	ALLOCATION_FAIL = 2,
} err_t;

typedef enum
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
} dir_t;
typedef enum
{
	EMPTY_CELL = 0,
	SHIP_CELL = 1,
	SHIP_PERIMETER_CELL = 2,
} cell_t;

typedef struct
{
	cell_t** m_grid;
} board_t;

/*Debugging tools*/
void printBoard(board_t* board);
/******************/

board_t* createBoard();

void destroyBoard(board_t** board);

err_t initRandBoard(board_t* board);
