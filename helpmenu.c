#include <ncurses.h>
#include <string.h>

void showhelp(void);

WINDOW *help;
const char HELP_TITLE[] = "Help Menu";

int main(void) {
		int ch;

		initscr();

		// create the help window to display later
		help = newwin(6, 50, 5, 5);
		mvwaddstr(help, 0, (50 - strlen(HELP_TITLE)) / 2, "Help Menu");
		mvwaddstr(help, 1, 0, "Press Q to quit");
		mvwaddstr(help, 2, 0, "Press ENTER to go back");

		addstr("Typewriter Program\n");
		addstr("Press ~ for help\n");
		refresh();
		noecho();

		do {
				ch = getch();
				if (ch == '~') 
						showhelp();
				else {
						addch(ch);
				}

		} while (ch != 'q');

		endwin();
		return 0;
}

void showhelp(void) {
		touchwin(help);
		wrefresh(help);
		getch();
		touchwin(stdscr);
		refresh();
}
