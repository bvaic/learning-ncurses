#include <ncurses.h>
#include <stdlib.h>

int main(void) {
	int rand_row;
	int rand_col;
	
	initscr();

	while ( getch() != 'q' ) {
		rand_row = rand() % LINES;
		rand_col = rand() % COLS;

		move(rand_row, rand_col);

		addch('*');
	}

	endwin();
	return 0;
}	
