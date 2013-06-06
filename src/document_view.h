#ifndef DOCUMENT_VIEW_H
#define DOCUMENT_VIEW_H

class DocumentView {
protected:
	int x_size;
	int y_size;
public:
	DocumentView();
	DocumentView(int x_size, int y_size);
	virtual void display(int x_screen_start, int y_screen_start, char * text) = 0;
	virtual bool resize(int x_size, int y_size);
};

#endif /* DOCUMENT_VIEW_H */
