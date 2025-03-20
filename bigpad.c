#include <ncurses.h>

int main() {
	WINDOW *pad;

	initscr();
	refresh();

	pad = newpad(100, 100);
	if (pad == NULL) {
		endwin();
		printf("Failed to create pad\n");
		return 1;
	}

	waddstr(pad, "This is on the big pad.\n");
	prefresh(pad, 0, 0, 0, 0, 1, 50);
	getch();

	endwin();
	return 0;
}
