#include <ncurses.h>

int main(void) {
	initscr();

	addstr("Press any key to start loop\n");
	refresh();
	getch();

	nodelay(stdscr, TRUE);
	while (1) {
		if (getch() == ' ') // only spacebar stops the loop
			break;
		addstr("blah ");
		refresh();
		napms(100);
	}
	
	nodelay(stdscr, FALSE);
	addstr("\nTarget key was pressed, loop ended\n");
	getch();

	endwin();
	return 0;
}
