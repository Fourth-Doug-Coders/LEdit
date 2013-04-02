#ifndef VIEW_H
#define VIEW_H

#include <iostream>

class DocumentView {
protected:
	int start_x;
	int start_y;
	int x_size;
	int y_size;
public:
	DocumentView();
	DocumentView(int start_x, int start_y, int x_size, int y_size);
	//waiting on Josh
	virtual void display() = 0;
	virtual bool resize(int start_x, int start_y, int x_size, int y_size);
	virtual bool reposition(int start_x, int start_y);
};

#endif /* VIEW_H */
