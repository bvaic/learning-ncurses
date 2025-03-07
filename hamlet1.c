#include <ncurses.h>
#include <string.h>

int main(void) {
	char Ham1[] = "To be, or not to be: that is the question:\n";
	char Ham2[] = "Whether 'tis nobler in the mind to suffer\n";
	char Ham3[] = "The slings and arrows of outrageous fortune,\n";
	char Ham4[] = "Or to take arms against a sea of troubles,\n";
	char Ham5[] = "And by opposing end them?\n";

	char addition[] = "obnoxious ";
	char *a;
	int len;

	initscr();

	addstr(Ham1);
	addstr(Ham3);
	addstr(Ham5);
	refresh();
	getch();

	move(1, 0);
	insertln(); // making a blank line for new Hamlet text
	addstr(Ham2);
	getch();

	move(3, 0);
	insertln();
	addstr(Ham4);
	getch();

	// removing 'outrageous' from row 2, col 25 (11 characters to del)
	move(2, 25);
	for (int i = 0; i < 11; i++) {
		delch();
		napms(100);
		refresh();
	}
	getch();

	// adding in 'obnoxious'
	move(2, 25);
	a = addition;
	len = strlen(addition);
	while (len) {
		insch(*(a + len - 1));
		refresh();
		napms(100);

		len--;
	}
	getch();

	// testing deleteln()
	move (0, 0);
	deleteln();
	getch();	
	
	endwin();
	return 0;
}
