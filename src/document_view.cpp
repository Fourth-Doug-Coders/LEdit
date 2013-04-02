#include "document_view.h"
#include <iostream>

DocumentView::DocumentView(){
	start_x = 0;
	start_y = 0;
	x_size = 0;
	y_size = 0;
}

View::DocumentView(int start_x, int start_y, int x_size, int y_size){
	this->resize(start_x, start_y, x_size, y_size);
}

bool DocumentView::resize(int start_x, int start_y, int x_size, int y_size){
	this->start_x = start_x;
	this->start_y = start_y;
	this->x_size = x_size;
	this->y_size = y_size;
}

bool DocumentView::reposition(int start_x, int start_y){
	resize(start_x, start_y, x_size, y_size);
}
