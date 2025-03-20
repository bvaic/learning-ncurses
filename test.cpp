#include <ncurses.h>
#include <iostream>
#include <string>

// write me a simple class structure below:
class SimpleClass {
public:
	SimpleClass() {
		std::cout << "SimpleClass constructor" << std::endl;
	}
	~SimpleClass() {
		std::cout << "SimpleClass destructor" << std::endl;
	}
};

int main() {
	initscr();

	addstr("Hello ncurses, this is C++");
	refresh();
	getch();

	endwin();

	SimpleClass obj;
}
