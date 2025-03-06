#include <ncurses.h>

const char CORNER = '*';
const int DELAY = 200; // ms

void corners(int, int);

int main(void) {
	initscr();
	start_color(); // terminal should be capable
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	int rows, cols;	
	getmaxyx(stdscr, rows, cols);
	rows--;
	cols--;
	
	printw("\nYour terminal has ");
	attrset(COLOR_PAIR(1));
	printw("%d", rows+1);
	attrset(A_NORMAL);
	printw(" rows and ");
	attrset(COLOR_PAIR(1));
	printw("%d", cols+1);
	attrset(A_NORMAL);
	printw(" columns.\n");

	int rows_center = rows / 2;
	int cols_center = cols / 2;
	
	printw("Center row: %d\n", rows_center);
	printw("Center col: %d\n", cols_center);	

	move(rows_center, cols_center);
	attrset(COLOR_PAIR(1) | A_BOLD);
	addch('*');
	attrset(A_NORMAL);
	addstr(" (center)");
	refresh();

	corners(rows, cols);
	move(4, 0);

	getch();
	endwin();
	return 0;
}

void corners(int rows, int cols) {
	attrset(COLOR_PAIR(1) | A_BOLD);

	// upper left
	mvaddch(0, 0, CORNER);
	refresh();
	napms(DELAY);

	// upper right
	mvaddch(0, cols, CORNER);
	refresh();
	napms(DELAY);

	// lower left
	mvaddch(rows, 0, CORNER);
	refresh();
	napms(DELAY);

	// lower right
	mvaddch(rows, cols, CORNER);
	refresh();
	napms(DELAY);
}
