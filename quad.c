#include <ncurses.h>
#include <stdlib.h>

void end(char *msg);

int main(void) {
		WINDOW *a, *b, *c, *d;
		int halfy, halfx;
		int ch;

		initscr();
		start_color();
		noecho();

		// create the window colors
		init_pair(1, COLOR_WHITE, COLOR_CYAN);
		init_pair(2, COLOR_WHITE, COLOR_RED);
		init_pair(3, COLOR_WHITE, COLOR_YELLOW);
		init_pair(4, COLOR_WHITE, COLOR_GREEN);

		// calculate the halves
		halfy = LINES >> 1;
		halfx = COLS >> 1;
	
		refresh();
		
		// create the windows
		if ( (a = newwin(halfy, halfx, 0, 0)) == NULL ) end("Unable to create window A");
		if ( (b = newwin(halfy, halfx, 0, halfx)) == NULL ) end("Unable to create window B");
		if ( (c = newwin(halfy, halfx, halfy, 0)) == NULL ) end("Unable to create window C");
		if ( (d = newwin(halfy, halfx, halfy, halfx)) == NULL ) end("Unable to create window D");
		
		// write to each windows
		mvwaddstr(a, 0, 0, "This is window A\n");
		wbkgd(a, COLOR_PAIR(1));
		wrefresh(a);
		mvwaddstr(b, 0, 0, "This is window B\n");
		wbkgd(b, COLOR_PAIR(2));
		wrefresh(b);
		mvwaddstr(c, 0, 0, "This is window C\n");
		wbkgd(c, COLOR_PAIR(3));
		wrefresh(c);
		mvwaddstr(d, 0, 0, "This is window D\n");
		wbkgd(d, COLOR_PAIR(4));
		wrefresh(d);
		
		do {
				ch = getch();
				waddch(a, ch);
				waddch(b, ch);
				waddch(c, ch);
				waddch(d, ch);
				wrefresh(a);
				wrefresh(b);
				wrefresh(c);
				wrefresh(d);
		} while (ch != 'q');

		endwin();
		return 0;
}	

void end(char *msg) {
		endwin();
		printf("\n%s\n\n", msg);
		exit(1);
}
