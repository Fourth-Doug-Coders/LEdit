#include <curses.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

vector<char> buffer;

void run();

int main(){
    WINDOW * win = initscr();
    int max_y = 80, max_x = 20;
    getmaxyx(win, max_y, max_x);
    noecho();
    raw();
    keypad(stdscr,TRUE);

    move(max_y - 2,0);
    hline(ACS_CKBOARD,max_x);
    mvaddstr(max_y -1,0,"LEdit. Ctrl-C to close.");

    run();

    clear();
    addstr("Exited text editor");
    getch();
    endwin();
    return 0;
}

void run(){
    int kP = 0;
    move(0,0);
    while(kP != KEY_F(1)){
        
        kP = getch();
        int i = 0;
        i++;
    }
}