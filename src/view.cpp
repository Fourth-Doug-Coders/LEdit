#include "view.h"
#include <iostream>

View::View(){
	start_x = 0;
	start_y = 0;
	x_size = 0;
	y_size = 0;
}

View::View(int start_x, int start_y, int x_size, int y_size){
	resize(start_x, start_y, x_size, y_size);
}

bool View::resize(int start_x, int start_y, int x_size, int y_size){
	this.start_x = start_x;
	this.start_y = start_y;
	this.x_size = x_size;
	this.y_size = y_size;
}

bool View::reposition(int start_x, int start_y){
	resize(start_x, start_y, x_size, y_size);
}

class View {
private:
	int start_x;
	int start_y;
	int x_size;
	int y_size;
public:
	virtual View();
	virtual View(int start_x, int start_y, int x_size, int y_size);
	virtual void display() = 0;
	virtual bool resize(int start_x, int start_y, int x_size, int y_size);
	virtual bool reposition(int start_x, int start_y);
};

#endif /* VIEW_H */
