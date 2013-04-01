#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "keystroke.h"

using namespace std;

vector<char> buffer;

void run(ostream&);

int main(){
    WINDOW * win = initscr();
    int max_y = 80, max_x = 20;
    getmaxyx(win, max_y, max_x);
    noecho();
    raw();
    keypad(stdscr,TRUE);

    move(max_y - 2,0);
    hline(ACS_CKBOARD,max_x);
    mvaddstr(max_y -1,0,"LEdit. Ctl-Q to close.");

    ofstream fout("log.txt");
    run(fout);

    clear();
    addstr("Exited text editor");
    getch();
    endwin();
    return 0;
}

void run(ostream &log){
    int kP = 0;
    move(0,0);

    Keystroke *ks = 0;
    while (ks == 0 || ks->shouldContinue()) {
	ks = getNextKeystroke();
	ks->log(log);
    }
}
