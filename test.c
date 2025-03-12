#include <ncurses.h>

#define LEFT 	0
#define CENTER 	1
#define RIGHT 	2

int main() {
	slk_init(0);
	initscr();

	slk_set(1, "Help [H]", CENTER);
	slk_refresh();
	getch();

	endwin();
	return 0;
}
