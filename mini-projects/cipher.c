#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

void err(char *msg);
int get_rot13(int ch);
int get_eol_col(WINDOW *win, int row);

int main(void) {
		int halfx, ch;
		WINDOW *a, *b;

		initscr();
		noecho();

		halfx = COLS >> 1;

		a = newwin(LINES, halfx, 0, 0);
		b = newwin(LINES, halfx, 0, halfx);
		keypad(a, TRUE); // for backspace

		refresh();

		wattrset(a, A_BOLD);
		wattrset(b, A_BOLD);

		mvwaddstr(a, 0, 0, "Normal Text\n");
		wrefresh(a);

		mvwaddstr(b, 0, 0, "Rot 13 Ciphertext\n");
		wrefresh(b);

		wattroff(a, A_BOLD);
		wattroff(b, A_BOLD);
	
		do {
				ch = wgetch(a);	
				if (ch == KEY_BACKSPACE) {
						int y, curX, newX;
						
						getyx(a, y, curX);
						newX = curX - 1;
						if (newX < 0) {
								wmove(a, y - 1, get_eol_col(a, y - 1));
								wdelch(a);
								// waddch(a, '*');
						}
						else {
								wmove(a, y, newX);
								wdelch(a);
								wmove(b, y, newX);
								wdelch(b);
						};	

						wrefresh(a);
						wrefresh(b);
				}
				else {
						waddch(a, ch);
						waddch(b, get_rot13(ch));

						wrefresh(a);
						wrefresh(b);
				}

		} while (ch != 'q');

		endwin();
		return 0;
}

int get_rot13(int ch) {
		char chrot13;
		bool upper = false;

		if (isupper(ch)) {
				upper = true;
				ch = tolower(ch);
		}

		if (!(ch >= 'a' && ch <= 'z')) return ch; // ignore things that aren't letters	

		if ((ch + 13) > 'z') { // for overflowing characters
				chrot13 = (13 - ('z' - ch) - 1) + 'a'; 
		}
		else {
				chrot13 = ch + 13;
		}

		if (upper) return toupper(chrot13);
		else return chrot13;
}

int get_eol_col(WINDOW *win, int row) {
		// 1. go to far right
		// 2. keep going left until non-space character found or hit (row, 0)
		// 3. return col right after the last character 
		int y, max_cols, ch, cur_col;	
		getmaxyx(win, y, max_cols);
	
		cur_col = max_cols - 1;	

		wmove(win, row, cur_col);
		ch = winch(win);
		waddch(win, ch);
		while (ch == ' ') {
				cur_col--;
				if (cur_col == 0) return 0;
				wmove(win, row, cur_col);
				ch = winch(win);
		}

		return cur_col + 1;
}

void err(char *msg) {
		endwin();
		printf("\nError: %s\n\n", msg);
		exit(1);
}
