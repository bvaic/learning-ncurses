#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define BOX_UL "\u250c"
#define BOX_UR "\u2510"
#define BOX_LL "\u2514"
#define BOX_LR "\u2518"
#define BOX_BAR "\u2500"
#define BOX_SIDE "\u2502"

#define TPOS_LEFT 0
#define TPOS_CENTER 1
#define TPOS_RIGHT 2

#define waddstrctr(win, row, text) \
	int wy, wx; \
	getyx(win, wy, wx); \
	mvwaddstr(win, row, (wx - strlen(text)) / 2, text);

const int HELP_LINES = 10;
const int HELP_COLS = 26;

WINDOW *help_win;

void draw_win_outline(WINDOW *win, int rows, int cols, char *title, int tpos);
void create_help_win();
void getyx_center_win(int rows, int cols, int *y, int *x);
void err_exit(char *msg, ...);


int main(int argc, char *argv[]) {
	int ch;

	setlocale(LC_ALL, "");

	initscr();

	create_help_win();

	addstr("test");
	refresh();

	do {
		ch = getch();

		switch (ch) {
			case '~':
				wrefresh(help_win);
				break;
		}
	} while (ch != 'q');
	// wrefresh(help_win);

	getch();

	endwin();
	return 0;
}

// Draws window outline with title, no refresh
// tpos (title position): 0 = left, 1 = center, 2 = right
void draw_win_outline(WINDOW *win, int rows, int cols, char *title, int tpos) {
	int title_len = strlen(title);	

	// top
	mvwaddstr(win, 0, 0, BOX_UL);

	// no checking if title fits in the top row (yet?)
	if (title_len + 2 > cols - 2)
		err_exit("Cannot draw window outline, no room for title (length %d, with spacing) on %d area", title_len + 2, cols - 2);
	
	for (int i = 1; i < cols - 1; i++) { mvwaddstr(win, 0, i, BOX_BAR); }
	switch (tpos) {
		case 0:
			mvwprintw(win, 0, 1, " %s ", title);
			break;
		case 1:
			int start_col = (cols - title_len - 1) / 2; // accounts for spaces around title
			mvwprintw(win, 0, start_col, " %s ", title);
			break;
		case 2:
			mvwprintw(win, 0, cols - title_len - 3, " %s ", title);
			break;
	}

	for (int i = 0; i < cols; i++) {
		wmove(win, 0, i);
	}
	mvwaddstr(win, 0, cols - 1, BOX_UR);

	// middle
	for (int i = 1; i < rows - 1; i++) {
		mvwaddstr(win, i, 0, BOX_SIDE); 
		mvwaddstr(win, i, cols - 1, BOX_SIDE); 
	}
	
	// bottom
	mvwaddstr(win, rows - 1, 0, BOX_LL);
	for (int i = 1; i < cols - 1; i++) {
		mvwaddstr(win, rows - 1, i, BOX_BAR);
	}
	mvwaddstr(win, rows - 1, cols - 1, BOX_LR);
}

// Create only, does not draw
void create_help_win() {
	int start_y = 0;
	int start_x = 0;
	getyx_center_win(5, HELP_COLS, &start_y, &start_x);

	help_win = newwin(HELP_LINES, HELP_COLS, start_y, start_x);
	draw_win_outline(help_win, HELP_LINES, HELP_COLS, "Help", TPOS_CENTER);
	waddstrctr(help_win, HELP_LINES - 1, " ENTER to return ");
}

// Waits for user to press ENTER, then closes
void open_help_win() {
	int ch;
	wrefresh(help_win);
	do { ch = getch(); } while (ch != '\n');

	// close
}

// Calculates the (y, x) point of the UL corner of a window to be drawn at the center of the screen 
void getyx_center_win(int rows, int cols, int *y, int *x) {
	int start_y = (LINES - rows) / 2;
	int start_x = (COLS - cols) / 2;
	*y = start_y;
	*x = start_x;	
}

// Takes formated msg
void err_exit(char *msg, ...) {
	va_list args;
	va_start(args, msg);

	char buffer[512];

	vsnprintf(buffer, sizeof(buffer), msg, args);

	endwin();
	printf("\nError: %s\n\n", buffer);

	va_end(args);
	exit(1);
}
