#include "document_view.h"
#include <iostream>

DocumentView::DocumentView(){
	x_size = 0;
	y_size = 0;
}

DocumentView::DocumentView(int x_size, int y_size){
	this->resize(x_size, y_size);
}

bool DocumentView::resize(int x_size, int y_size){
	this->x_size = x_size;
	this->y_size = y_size;
}