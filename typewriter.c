#include <ncurses.h>

int main(void) {
	initscr();

	char ch;

	addstr("This is a typewriter. Press 'q' to quit.\n");
	refresh();

	while ( (ch = getch()) != 'q')
		;

	endwin();
	return 0;
}
