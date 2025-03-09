#include <ncurses.h>

#define MENU_ITEMS 4

const char MENU_TITLE[] = "Main Menu";

// positioning
const int MENU_STARTING_ROW = 5;
const int MENU_COL = 10;

// draw menu with item reversed (selected)
void draw_menu(int item) {
	char menu[MENU_ITEMS][32] = {
		"Browse the Internet",
		"Read E-Mail",
		"Word processing",
		"Shutdown"
	};

	mvaddstr(0, 5, MENU_TITLE);
	
	for (int i = 0; i < MENU_ITEMS; i++) {
		if (i == item)
			attron(A_REVERSE);
		mvaddstr(MENU_STARTING_ROW + (i * 2), MENU_COL, menu[i]);
		attroff(A_REVERSE);
	}

	mvaddstr(MENU_STARTING_ROW + (MENU_ITEMS * 2) + 3, 5, "Use arrow keys to move, ENTER to select.");
	refresh();
}

int main(void) {
	int key, menuitem;	

	menuitem = 0;

	initscr();

	noecho();
	keypad(stdscr, TRUE);
	draw_menu(menuitem);

	do {
		key = getch();
		switch (key) {
			case KEY_UP:
				menuitem--;
				if (menuitem < 0)
					menuitem = 0;
				break;
			case KEY_DOWN:
				menuitem++;
				if (menuitem > MENU_ITEMS - 1)
					menuitem = MENU_ITEMS - 1;
				break;
		}
		draw_menu(menuitem);
	} while (key != '\n');

	echo();

	// the value of menuitem can be used in a switch statement to determine what to do next

	endwin();
	return 0;
}
