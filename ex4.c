#include <ncurses.h>

int main(){

	initscr();
	raw();

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLUE);
	attron(COLOR_PAIR(1));
	printw("Hi Guys my name is John Cena!");
	attroff(COLOR_PAIR(1));

	getch();
	endwin();

	return 0;
}
