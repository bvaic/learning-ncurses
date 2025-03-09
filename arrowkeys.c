#include <ncurses.h>

int main(void) {
	int ch;

	initscr();
	keypad(stdscr, TRUE);		
	noecho();

	addstr("Press the arrow keys. Press 'q' to quit.\n");

	do {
		ch = getch();
		switch (ch) {
			case KEY_UP:
				addstr("up\n");
				break;
			case KEY_DOWN:
				addstr("down\n");
				break;
			case KEY_LEFT:
				addstr("left\n");
				break;
			case KEY_RIGHT:
				addstr("right\n");
				break;
		}
		refresh();

	} while (ch != 'q');

	endwin();
	return 0;
}
