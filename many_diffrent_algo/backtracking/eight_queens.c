#include <stdio.h>

#define AMOUNT_OF_QUEEN 8
void DEBUG_PRINT_BOARDCOODINATES() {
	puts("==========DEBUG=========");
	puts("down - display (row - col)");
	for(int row=0; row<AMOUNT_OF_QUEEN; ++row){
		for(int col=0; col<AMOUNT_OF_QUEEN; ++col) printf("%2d ", row-col);
		puts("");
	}
	puts("down - display (row - col + AMOUNT_OF_QUEEN-1)");
	for(int row=0; row<AMOUNT_OF_QUEEN; ++row){
		for(int col=0; col<AMOUNT_OF_QUEEN; ++col) printf("%2d ", row-col+AMOUNT_OF_QUEEN-1);
		puts("");
	}
	puts("up - display (row + col)");
	for(int row=0; row<AMOUNT_OF_QUEEN; ++row){
		for(int col=0; col<AMOUNT_OF_QUEEN; ++col) printf("%2d ", row+col);
		puts("");
	}
	puts("========================");
}

#define FREE 0
#define ATTACKED 1
#define EMPTY -1
typedef struct _board{
	int pos[AMOUNT_OF_QUEEN],
	    col[AMOUNT_OF_QUEEN],
	    down[2*AMOUNT_OF_QUEEN-1],
	    up[2*AMOUNT_OF_QUEEN-1];
} Board;

void init(Board *const board){
	for(int i = 0; i < AMOUNT_OF_QUEEN; ++i){
		board->pos[i] = EMPTY;
		board->col[i] = FREE;
	}
	for(int i = 0; i < 2*AMOUNT_OF_QUEEN-1; ++i){
		board->down[i] = FREE;
		board->up[i] = FREE;
	}
}

void print_board(const Board *const board){
	for(int row = 0; row < AMOUNT_OF_QUEEN; ++row){
		puts("");
		for(int col = 0; col < AMOUNT_OF_QUEEN; ++col){
			const char display_char = (board->pos[row] == col) ? 'Q' : '.'; // Q is queen
			putchar(display_char);
			putchar(' ');
		}
	}
}

#define SUCCESS 0
#define FAILURE 1
int try(const int row, Board *const board){
	for(int column = 0; column < AMOUNT_OF_QUEEN; ++column){
		const int is_attacked = ((board->col[column] == ATTACKED)||
					(board->down[row-column+AMOUNT_OF_QUEEN-1] == ATTACKED)||
					(board->up[row+column] == ATTACKED));
		if(is_attacked) continue;
		// place a queen on a board.
		board->pos[row] = column;
		board->col[column] = ATTACKED;
		board->down[row-column+AMOUNT_OF_QUEEN-1] = ATTACKED;
		board->up[row+column] = ATTACKED;
		if(row >= (AMOUNT_OF_QUEEN-1)) return SUCCESS;

		const int result = try(row+1, board);
		if(result == SUCCESS) return SUCCESS;
		// reset to retry
		board->pos[row] = EMPTY;
		board->col[column] = FREE;
		board->down[row-column+AMOUNT_OF_QUEEN-1] = FREE;
		board->up[row+column] = FREE;
	}
	return FAILURE;
}

int main(){
	DEBUG_PRINT_BOARDCOODINATES();

	Board board;
	init(&board);
	print_board(&board);
	puts("");
	if (try(0, &board) == SUCCESS)
		print_board(&board);

	return 0;
}
