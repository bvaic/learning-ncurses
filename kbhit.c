#include <ncurses.h>

int kbhit(void) {
	int ch, r;

	// turn off getch() blocking and echo
	nodelay(stdscr, TRUE);
	noecho();

	// check for input
	ch = getch();
	if (ch == ERR)
		r = FALSE;
	else {
		r = TRUE;
		ungetch(ch); // if there is a character waiting, put it back into the queue
	}

	// restore block and echo
	echo();
	nodelay(stdscr, FALSE);
	return(r);
}
	
int main(void) {
	initscr();

	addstr("Press any key to end this loop\n");
	while (!kbhit()) {
		addstr("blah ");
		napms(100);
	}

	endwin();
	return 0;
}
