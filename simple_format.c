#include <ncurses.h>

int main(void) {
	initscr();

	attrset(A_BLINK);
	printw("This should be blinking\n");

	attrset(A_BOLD);
	printw("Bold! hahahah");
	refresh();

	getch();
	endwin();
	return 0;
}
