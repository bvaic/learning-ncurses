#include <ncurses.h>

const int DELAY = 50;

int main(void) { // the void means a 'function that expects no arguments'
	char sentences[][100] = {
		"This is Ben's little sentece.",
		"Hello professor Falken.",
		"Would you like to play a game?"
	};
	int number_of_sentences = sizeof(sentences) / sizeof(sentences[0]);

	initscr();

	for (int i = 0; i < number_of_sentences; i++) {
		char *t = sentences[i];	

		while (*t) { // while dereferenced pointer is not NULL (exists)
			addch(*t);
			t++; // increment the pointer
			refresh();
			napms(DELAY); // sleeping for a bit
		}
		addch('\n');
		napms(DELAY);
	}

	getch();
	endwin();
	return 0;
}
