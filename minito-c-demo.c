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

#define EDIT_LIMIT 

// STATES (linked to global var: 
#define INSERT 0

#define waddstrctr(win, row, text) \
	int wy, wx; \
	getyx(win, wy, wx); \
	mvwaddstr(win, row, (wx - strlen(text)) / 2, text);

typedef struct TaskNode {
	int task_id;
	//int depth;
	bool complete;
	char text[300];

	//struct TaskNode *subtask; // if implemented, this would lead to another linked list for the subtasks
	struct TaskNode *prev;
	struct TaskNode *next;
} TaskNode;

const char SELECTED_PREFIX[] = " --> ";
const char TASK_BOX_NORMAL[] = "[ ]";
const char TASK_BOX_COMPLETE[] = "[X]";
const int HELP_LINES = 10;
const int HELP_COLS = 26;
const char state_def[][50] = {
	"INSERT"
};

// GLOBALS
WINDOW *help_win;
char filename[400] = "untitled"; // may need increase buffer size
TaskNode *selected_task;

short state = INSERT;

void draw_screen();
void enter_pressed();
void delch_on_taskline();
void draw_win_outline(WINDOW *win, int rows, int cols, char *title, int tpos);
void create_help_win();
void open_help_win();
void getyx_center_win(int rows, int cols, int *y, int *x);
void wprintwctr(WINDOW *win, int row, char *fmt, ...);
void err_exit(char *msg, ...);


int main(int argc, char *argv[]) {
	int ch;
	bool loop;

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	keypad(stdscr, TRUE);

	create_help_win();

	draw_screen();	

	refresh();

	loop = true;
	while (loop) {
		ch = getch();
		switch (ch) {
			case '\n':
				enter_pressed();	
				break;
			case KEY_BACKSPACE:
				delch_on_taskline();
				break;
			case '~':
				open_help_win();
				break;
			case 'q':
				if (state != INSERT)
					loop = false;
				else
					addch(ch);
				break;
			default:
				addch(ch);
				refresh();	
				break;
		}
	};

	endwin();
	return 0;
}

/*
draws:
1. title
2. tasks
3. state
*/
void draw_screen() {
	// title
	wprintwctr(stdscr, 0, "Minito - %s", filename);

	// tasks
	attrset(A_BOLD);
	mvprintw(1, 0, "%s%s ", SELECTED_PREFIX, TASK_BOX_NORMAL);
	
	// state
	mvprintw(LINES-1, 1, "%s", state_def[state]);
	
	// move back to first task
	move(1, strlen(SELECTED_PREFIX) + strlen(TASK_BOX_NORMAL) + 1);
}

void enter_pressed() {
	switch (state) {
		case INSERT:
			// create a task
			break;
	}
}

// Move first then delete, not the other way around
void delch_on_taskline() {
	int edit_limit = strlen(SELECTED_PREFIX) + strlen(TASK_BOX_NORMAL);
	int y, curX, newX;
	
	getyx(stdscr, y, curX);
	newX = curX - 1;
	if (newX > edit_limit) {
		move(y, newX);
		delch();
		refresh();
	}
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
	wprintwctr(help_win, HELP_LINES - 1, " ENTER to return ");
}

// Waits for user to press ENTER, then closes
void open_help_win() {
	int ch;
	touchwin(help_win);
	wrefresh(help_win);
	do { ch = getch(); } while (ch != '\n');

	// close
	touchwin(stdscr);
	refresh();	
}

// Calculates the (y, x) point of the UL corner of a window to be drawn at the center of the screen 
void getyx_center_win(int rows, int cols, int *y, int *x) {
	int start_y = (LINES - rows) / 2;
	int start_x = (COLS - cols) / 2;
	*y = start_y;
	*x = start_x;	
}

// Prints at center of given row of given window
void wprintwctr(WINDOW *win, int row, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	char buffer[512];
	vsnprintf(buffer, sizeof(buffer), fmt, args);

	int wx = getmaxx(win);
	mvwaddstr(win, row, (wx - strlen(fmt)) / 2, buffer);

	va_end(args);
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
