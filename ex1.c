# include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(){
	initscr();
	raw();
	printw("Hello World!");
	getch();
	endwin();

	return 0;
}
