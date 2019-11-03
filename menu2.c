#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <menu.h>


int main(int argc, char *argv[])
{
    int i, c;
    char powitanie[]="SLOWNIK UNIWERSALNY";
    int szer, dlug; //wartosci dlugosci i szerokosci terminalu
    initscr(); //Inizjalizacja całości ncurses, kolory itp
    raw();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    //init_pair(1, COLOR_BLUE, COLOR_BLACK); //wybór kolorów
    getmaxyx(stdscr, szer, dlug); //pobranie rozmiarów terminalu
    move(szer/2, (dlug-strlen(powitanie))/2); //przesuwamy kursor na środek (tak aby się ładnie wydrukowało)
    //attron(COLOR_PAIR(1)); //Aktywujemy wybrane kolory
    printw(powitanie); //Drukujemy powitanie
    //attroff(COLOR_PAIR(1));//Dezaktywujemy kolory
    refresh();//Odswiezamy (inaczej się nie wyswietli)
    WINDOW * menuwin=newwin(6, dlug-12, szer-8, 6); //Definiujemy i tworzymy 'okno'
    box(menuwin, 0, 0);
    refresh();//ponownie odświeżamy aby okno się pojawiło
    wrefresh(menuwin);//odświeżamy samo okno
    keypad(menuwin, TRUE);//umozliwiamy dzialanie klawiatury w oknie
    char *opcje[] = {
                        "Tlumacz z Polskiego na Angielski",
                        "Tlumacz z Angielskiego na Polski",
                        "Edystuj slownik",
                        "Wybierz slownik",
                        "Wyjdz",
                  };
    int wybor;
    int zaznacz=0;
    while(1)//cala ta petla sluzy ciaglemu tworzeniu menu z podswietleniem wybranego elementu
    {
        for(i=0; i<5; i++)
        {
            if(i==zaznacz)
            {
                wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i+1, 1, opcje[i]);
                wattroff(menuwin, A_REVERSE);
            }
            wybor = wgetch(menuwin);
            switch(wybor)
            {
                case KEY_UP:
                zaznacz--;
                if(zaznacz==-1) zaznacz=0;//zabezpieczenie przed wyjsciem "poza" menu
                break;
                case KEY_DOWN:
                zaznacz++;
                if(zaznacz==5) zaznacz=4;
                break;
                default:
                break;
            }
            if(wybor==10) break;
        }
        printw("Wybrano:%s", opcje[zaznacz]);
    }
    return(0);
}
