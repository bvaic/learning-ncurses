#include <ncurses.h>

int main(void) {
	char username[32];
	char password[32];

	initscr();

	mvprintw(5, 10, "Enter your username: ");
	refresh();
	getnstr(username, 32);

	noecho();
	mvprintw(6, 10, "Enter your password: ");
	refresh();
	getnstr(password, 32);

	mvprintw(8, 10, "Hello %s, your password (%s) is safe with me.", username, password);
	refresh();
	getch();

	endwin();
	return 0;
}
