#include <ncurses.h>

int main(void) {
	initscr();

	int i, y, x, max;

	getmaxyx(stdscr, y, x);

	char blah[] = "blah "; // 5 characters
	max = (x * y) / 5; // how many 5-character blahs can fit in the screen area
	for (i = 0; i < max; i++)
		addstr(blah);
	refresh();
	getch();

	//clear();
	//refresh();
	//getch();
	
	move(5, 20);
	clrtoeol();
	refresh();
	getch();

	move(7, 10);
	clrtobot();
	refresh();
	getch();

	endwin();
	return 0;
}	
