#include <ncurses.h>

int main(void) {
	char first[25];
	char last[25];

	initscr();

	printw("Welcome to Ben's Input Form\n");

	printw("Please enter your first name: ");
	refresh();
	getnstr(first, 24);
	
	printw("Please enter your last name: ");
	refresh();
	getnstr(last, 24);

	printw("Welcome, %s %s.", first, last);
	refresh();

	getch();
	endwin();
	return 0;
}
