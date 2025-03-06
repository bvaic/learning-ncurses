#include <ncurses.h>
#include <stdlib.h>

#define COLOR_ORANGE 1

void end(char *msg); // function prototype!

int main(void) {
	initscr();

	// check 1
	if (!has_colors())
		end("Your terminal does not support color.\n");

	// check 2
	if (start_color() != OK)
		end("Couldn't initialize color utilities.\n");

	printw("Colors have been properly initialized!\n");
	printw("You can use %d colors\n", COLORS);
	printw("and %d color pairs.\n", COLOR_PAIRS);

	// color test
	init_pair(1, COLOR_RED, COLOR_WHITE);
	attrset(COLOR_PAIR(1) | A_BOLD);
	addstr("This is a test warning!\n");

	// color test 2
	init_pair(2, 3, 1);
	attrset(COLOR_PAIR(2));

	attrset(A_NORMAL);
	printw("\nLooping through available colors (%d):\n", COLORS);
	for (int i = 0; i < COLORS; i++) {
		init_pair(i+3, 0, i);
		attrset(COLOR_PAIR(i+3));
		addch(' ');
	}
	addch('\n');
	attrset(A_NORMAL);

	// custom colors with r,g,b
	if (!(can_change_color()))
		addstr("\nTerminal cannot define colors.\n");
	else {
		addstr("\nTerminal able to define colors!\n");

		short r = 956; // 244
		short g = 466; // 119
		short b = 141; // 36
		init_color(COLOR_ORANGE, r, g, b);
		init_pair(2, COLOR_BLACK, COLOR_ORANGE);
		attrset(COLOR_PAIR(2));
		addstr("This is a custom defined orange.\n");
	}

	refresh();
	getch();
	endwin();
	return 0;
}

void end(char *msg) {
	endwin();
	puts(msg);
	exit(1);
}
