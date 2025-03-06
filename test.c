#include <ncurses.h>

int main() {
	initscr();

	addstr("This is a test message\n");
	addstr("Enter something: ");	

	refresh();
	
	char answer[100];
	getnstr(answer, 99);

	printw("You said:\n%s", answer);
	refresh();

	getch();
	endwin();
	return 0;
}
