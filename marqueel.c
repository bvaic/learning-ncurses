#include <ncurses.h>
#include <string.h>

int main(void) {
	char text[] = "Bitcoin soaring! Now in the upper 90,000s!";
	char *t;
	int len;

	initscr();

	t = text;
	len = strlen(text);

	while (len) {
		move(5, 5);
		insch(*(t + len - 1));
		refresh();
		napms(100);
			
		len--;
	}
	getch();
		
	endwin();
	return 0;
}
