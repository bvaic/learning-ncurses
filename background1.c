#include <ncurses.h>

int main(void) {
	initscr();

	if (!(has_colors()) || (start_color() != OK)) {
		endwin();
		return 1;
	}

	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	bkgd('~' | COLOR_PAIR(1));
	refresh();

	getch();
	endwin();
	return 0;
}
