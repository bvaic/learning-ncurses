#include <ncurses.h>

int main(void) {
	
	initscr();

	for (int i = 0; i < 4; i++) { 
		move(i, i * 4);
		addstr("Hello");
		refresh();
	}

	getch();

	endwin();
	return 0;
}
