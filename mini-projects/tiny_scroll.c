#include <ncurses.h>

const int LINE_LIMIT = 10;

int main(int argc, char *argv[]) {
	FILE *f;	
	char buffer[255];
	
	if (argc == 1) {
		printf("Filename required\n");
		return 1;
	}

	f = fopen(argv[1], "r"); // potential vuln? user defined filename?
                             
    if (f == NULL) {
		printf("File not found\n");
		return 1;
	}

	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	printw("Tiny scrolling %s", argv[1]); 

	bool lines_left = true;
	while (lines_left) {
		move(1, 0);
		clrtobot(); // clear command!

		attrset(COLOR_PAIR(1));
		addstr("***\n");
		attrset(A_NORMAL);

		for (int i = 0; i < LINE_LIMIT; i++) {
			if (fgets(buffer, 255, f) != NULL)
				addstr(buffer);
			else
				lines_left = false; 
		}

		attrset(COLOR_PAIR(1));
		addstr("***");
		attrset(A_NORMAL);
		
		refresh();
		getch();
	}

	fclose(f);
	endwin();
	return 0;
}
