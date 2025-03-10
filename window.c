#include <ncurses.h>

int main(void) {
		WINDOW *two;

		initscr();
		start_color();

		init_pair(1, COLOR_CYAN, COLOR_BLACK);

		two = newwin(4, 50, 3, 3);
		if (two == NULL) {
				addstr("Unable to allocate memory for the window.\n");
				refresh();
				getch();
				return 1;
		}
		mvwaddstr(two, 0, 0, " This is in the new window\n");
		wattrset(two, COLOR_PAIR(1) | A_BOLD);
		mvwaddch(two, 0, 0, '*');
		mvwaddch(two, 3, 0, '*');
		mvwaddch(two, 0, 49, '*');
		mvwaddch(two, 3, 49, '*');
		wattroff(two, COLOR_PAIR(1));
		refresh(); // apparently this needs to come before wrefresh() and not after
		wrefresh(two);
		getch();

		endwin();
		return 0;
}
