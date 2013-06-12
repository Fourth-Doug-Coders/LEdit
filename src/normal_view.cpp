#include "normal_view.h"
#include <iostream>
#include <curses.h>

using namespace std;

void NormalView::display(const vector< string > & text, int x_screen_start, int y_screen_start)
{
	//TODO: actually display this thing.  
	for(int i = 0; i < y_size; i++){
		mvaddstr(i, 0, text[i].c_str());
	}
}
