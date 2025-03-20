#include <ncurses.h>

#define CENTER 1

int main() {
	char labels[][8] = {"Test", "Label2", "Label3", "Label4",
		"Label5", "Label6", "Label7", "Label8",
		"Label9", "Label10", "Label11", "Label12"};

	slk_init(3);
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(2);
	slk_restore();

	for (int i = 0; i < 12; i++) 
		slk_set(i + 1, labels[i], CENTER);
	slk_refresh();

	int ch;
	while ( (ch = getch()) != 'q' ) {
		switch (ch) {
			case KEY_F(1):
				addstr("F1 pressed");
				break;
			case KEY_F(2):
				addstr("F2 pressed");
				break;
			case KEY_F(3):
				addstr("F3 pressed");
				break;
			case KEY_F(4):
				addstr("F4 pressed");
				break;
			case KEY_F(5):
				addstr("F5 pressed");
				break;
			case KEY_F(6):
				addstr("F6 pressed");
				break;
			case KEY_F(7):
				addstr("F7 pressed");
				break;
			case KEY_F(8):
				addstr("F8 pressed");
				break;
			case KEY_F(9):
				addstr("F9 pressed");
				break;
			case KEY_F(10):
				addstr("F10 pressed");
				break;
			case KEY_F(11):
				addstr("F11 pressed");
				break;
			case KEY_F(12):
				addstr("F12 pressed");
				break;
			default:
				addch(ch);
				break;

			refresh();
		}
	}

	/*
	slk_clear();
	getch();

	slk_set(2, "NEW", CENTER);
	slk_set(8, "", CENTER);
	slk_restore();
	getch();
	*/

	endwin();
	return 0;
}
