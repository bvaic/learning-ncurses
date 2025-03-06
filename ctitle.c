#include <ncurses.h>
#include <string.h>

void center(int row, char *text);

int main(void) {
	initscr();

	center(5, "Wow! Centered text!");
	center(7, "The penguin goes where the penguin wants.");

	//mvprintw(9, 0, "%7s", "Blah");
	//refresh();

	getch();
	endwin();
	return 0;
}

void center(int row, char *text) {
	int len, indent, y, width;
	getmaxyx(stdscr, y, width);

	len = strlen(text);
	indent = width - len;
	indent /= 2;

	mvaddstr(row, indent, text);
	refresh();
}
