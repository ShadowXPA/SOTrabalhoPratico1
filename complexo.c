#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define MAX_CLIENTE 2

#define LARGURA 50
#define ALTURA 10


int startx = 0;
int starty = 0;

char *vOpcoes[] = {
       "(1) Cadastrar os clientes e compras",
       "(2) Calcular e mostrar valor",
       "(3) Listar clientes cadastrados",
       "(4) salvar em arquivo",
       "(5) Sair",
};



struct TabCliente {

     char strNome[50],
          strCpf[20],
          strTelefone[15];
     float fCompra;
} regCliente[MAX_CLIENTE];



int n_opcoes = sizeof(vOpcoes) / sizeof(char *);

int qtdClientes=0;
double totalCompras=0;


void imprimirRotulo(WINDOW *tmpJanela,int y, int x, char *sRotulo){

    wattron(tmpJanela,COLOR_PAIR(1));
    mvwprintw(tmpJanela,y,x,sRotulo);
    wattroff(tmpJanela,COLOR_PAIR(1));

}


void print_menu(WINDOW *menu_win, int highlight) {

      int x,y,i;
      x = 2; 
      y = 2;

      box(menu_win,0,0);
      for(i=0; i< n_opcoes; i++){
          if(highlight == i+1) 
            {
               wattron(menu_win,A_REVERSE);
               mvwprintw(menu_win,y,x,"\t%s",vOpcoes[i]);
               wattroff(menu_win,A_REVERSE);
             }
           else
               mvwprintw(menu_win,y,x,"\t%s",vOpcoes[i]);
               ++y;
        }
        wrefresh(menu_win);
}


void incluir_cliente(){

    WINDOW *janela;
    char strCompra[20];
    int i, telaAltura, telaLargura;
    int startx, starty;


    init_pair(1,COLOR_GREEN,COLOR_BLACK);


    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;   
    startx = (COLS - telaLargura)/2; 
    refresh();

    janela = newwin(ALTURA,LARGURA,starty,startx);

    for(i=0;i<2;i++) {

        wborder(janela, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

        imprimirRotulo(janela,starty+1,startx+1,"Nome.:____________________");
        imprimirRotulo(janela,starty+2,startx+1,"CPF..:____________________");
        imprimirRotulo(janela,starty+3,startx+1,"Telefone.: _______________"); 
        imprimirRotulo(janela,starty+4,startx+1,"Valor Compra.:  __________"); 


        echo();
        wmove(janela,starty+1,startx+8);
        wgetstr(janela,regCliente[i].strNome);

        wmove(janela,starty+2,startx+8);
        wgetstr(janela,regCliente[i].strCpf);

        wmove(janela,starty+3,startx+12);
        wgetstr(janela,regCliente[i].strTelefone);

        wmove(janela,starty+4,startx+16);
        wscanw(janela,"%f",®Cliente[i].fCompra); 

        wclear(janela);
        wborder(janela, ' ', ' ', ' ',' ',' ',' ',' ',' ');  
        wrefresh(janela);

        qtdClientes+=1;

     }
    delwin(janela);

}



void listar_compras(){



    WINDOW *janela;
    char strCompra[20];
    int i, telaAltura, telaLargura;
    int startx, starty;


    init_pair(1,COLOR_GREEN,COLOR_BLACK);

    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;
    startx = (COLS - telaLargura)/2;
    refresh();


    janela = newwin(ALTURA,LARGURA,starty,startx);


    for(i=0;i<=qtdClientes-1;i++){
       wattron(janela,COLOR_PAIR(1));
       mvwprintw(janela,starty+(i+1),startx+1,"%s\t%f",regCliente[i].strNome,regCliente[i].fCompra);
       wattroff(janela,COLOR_PAIR(1));
       totalCompras+=regCliente[i].fCompra;
       wrefresh(janela);
   }

    init_pair(2,COLOR_RED,COLOR_BLACK);

    wattron(janela,COLOR_PAIR(2));
    wprintw(janela,"\n\nTotal da compra: %f",totalCompras);
    wattroff(janela,COLOR_PAIR(2));

    wrefresh(janela);
    getch();
    wrefresh(janela);


    delwin(janela);


}


void listar_clientes(){

     WINDOW *janela;
    char strCompra[20];
    int i, telaAltura, telaLargura;
    int startx, starty;




    getmaxyx(stdscr,telaAltura,telaLargura);
    starty = (LINES - telaAltura)/2;
    startx = (COLS - telaLargura)/2;
    refresh();


    janela = newwin(ALTURA,70,starty,startx);

    init_pair(1,COLOR_GREEN,COLOR_BLACK);


    wprintw(janela," Nome\t\t\tCPF\t\t\tTelefone");
    wrefresh(janela);

    for(i=0;i<=qtdClientes-1;i++){
       wattron(janela,COLOR_PAIR(1));
       mvwprintw(janela,starty+(i+1),startx+1,"%s\t\t%s\t\t%s",regCliente[i].strNome,
regCliente[i].strCpf,regCliente[i].strTelefone);
       wattroff(janela,COLOR_PAIR(1));
       wrefresh(janela);
   }


    getch();
    wrefresh(janela);
    delwin(janela);

}

void salvar_clientes() {
    int i;
    FILE *fp;

    fp=fopen("relCliente","ab");

    if(fp==NULL){
        fprintf(stderr,"\nNao foi possivel criar arquivo\n");
        exit(-1);
    }

    fprintf(fp,"Nome\t\tCPF\t\tTelefone\t\tVl. Compra\n"); 
    for(i=0;i<qtdClientes;i++){
       fprintf(fp,"\n%s",regCliente[i].strNome);
       fprintf(fp,"\t%s",regCliente[i].strCpf);
       fprintf(fp,"\t%s",regCliente[i].strTelefone);
       fprintf(fp,"\t%f",regCliente[i].fCompra);
    }

    fclose(fp);
}


void destruir_menu(WINDOW *menu_win){
    wclear(menu_win);
    wborder(menu_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(menu_win);
    delwin(menu_win);
}



int main() {

     WINDOW *menu_win;
     int highlight = 1;
     int opcao = 0;
     int c;

     initscr();

     if(has_colors() == FALSE)
     {
        endwin();
        printf("Seu terminal nao suporta cores\n");
        exit(1);
     }

     start_color();

     clear();
     noecho();
     cbreak();

     menu_win = newwin(ALTURA,LARGURA,starty,startx);
     keypad(menu_win,TRUE);
     refresh();

     do {

        print_menu(menu_win,highlight);
        c = wgetch(menu_win);

       switch(c) {
           case KEY_UP:
             if(highlight == 1)
                 highlight = n_opcoes;
             else
                 --highlight;
             break;
            case KEY_DOWN:
              if(highlight == n_opcoes)
                  highlight = 1;
               else
                  ++highlight;
               break;
            case 10:
                opcao = highlight;

                   if(opcao==1){
                      destruir_menu(menu_win);
                      incluir_cliente();
                      menu_win = newwin(ALTURA,LARGURA,starty,startx);
                      keypad(menu_win,TRUE);
                      refresh();
                    }

                   if(opcao==2){
                      destruir_menu(menu_win);
                      listar_compras();
                      menu_win = newwin(ALTURA,LARGURA,starty,startx);
                      keypad(menu_win,TRUE);
                      refresh();
                    }
                   if(opcao==3) {
                     destruir_menu(menu_win);
                     listar_clientes();
                     menu_win = newwin(ALTURA,LARGURA,starty,startx);
                     keypad(menu_win,TRUE);
                     refresh();
                    }
                   if(opcao==4)
                        salvar_clientes();
                   if(opcao==5){
                      goto sair;
                   }
               break;
            default:
                  refresh();
               break;
           }

        }while(1);

     sair:
        refresh();
        endwin();
        return 0;
}
