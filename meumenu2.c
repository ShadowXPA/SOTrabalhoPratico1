#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


int main(){
	char username[50];
	char password[30];

	initscr();
	raw();

	printw("Login\n");
	printw("Username:\n");
	move(2,0);
	//fgets(username, 50, stdin);
	//scanf("%s", username);
	getstr(username);
	//getch();

	printw("Password:\n");
	move(4,0);
	//fgets(password, 30, stdin);
	//scanf("%s", password);
	//mvprintw(3,0,"\nPassword:");
	getstr(password);
	//getch();

	printw("Username: %s\nPassword: %s\n",username,password);

	getch();
	endwin();

	return 0;
}

