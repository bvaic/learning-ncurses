#include <ncurses.h>

int main() {
    WINDOW *alpha;
    char text1[] = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nubh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat.";
    char text2[] = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.";

    initscr();

    alpha = newwin(0, 0, 0, 0);

    addstr(text1);
    refresh();
    getch();

    waddstr(alpha, text2);
    wrefresh(alpha);
    getch();

    overwrite(stdscr, alpha);
    wrefresh(alpha);
    getch();

    endwin();
    return 0;
}