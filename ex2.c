#include <ncurses.h>

int main(){

	initscr();
	raw();
	int x = 4;
	printw("Valor de x: %d", x);
	addch('a');
	move(12,13);

	mvprintw(15,20,"Movement");
	mvaddch(12,50,'@');

	getch();
	endwin();

	return 0;
}
