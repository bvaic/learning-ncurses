#include <ncurses.h>

const int COL1 = 5;
const int COL2 = 40;

int main(void) {
	initscr();

	mvprintw(5, COL1, "%30s", "Name:");
	mvprintw(5, COL2, "%-30s", "John Smith");

	getch();
	endwin();
	return 0;
}
