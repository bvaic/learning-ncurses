#include <ncurses.h>
#include <string.h>

#define DELAY_MS 50

void moveWin(WINDOW *win, int newY, int newX);

int main() {
	WINDOW *win;
	WINDOW *subwin;
	char winTitle[] = " Scrolling a File ";
	FILE *file;

	initscr();

	// a window to contain everything and a subwindow for the scrolling text

	// making a window
	int winColumns = 40;
	int winRows = 10;
	win = newwin(winRows, winColumns, 5, 5);
	//wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	box(win, '|', '-');
	mvwaddstr(win, 0, (winColumns - strlen(winTitle)) / 2, winTitle);	

	// making a subwindow
	subwin = derwin(win, winRows - 2, winColumns - 2, 1, 1);	
	scrollok(subwin, TRUE); // important: allows scrolling
	
	// displaying the window
	refresh();
	wrefresh(win);

	getch();

	// scrolling a file
	file = fopen("data/poem.txt", "r");
	if (file == NULL) {
		endwin();
		printf("Error opening file");
		return 1;
	}
	int character;
	do {
		character = fgetc(file);
		waddch(subwin, character);
		wrefresh(subwin);
		//beep();
		napms(DELAY_MS);

	} while (character != EOF);
	fclose(file);

	getch();

	// moving the window somewhere else for fun
	moveWin(win, 10, 10);
	getch();
	moveWin(win, 20, 20);
	getch();

	endwin();
	return 0;
}

void moveWin(WINDOW *win, int newY, int newX) {
	touchwin(stdscr);		// 1. wipe the stdscr
	refresh();				// 2. refresh stdscr 
	mvwin(win, newY, newX); // 3. move the window
	wrefresh(win);			// 4. refresh the window
}
