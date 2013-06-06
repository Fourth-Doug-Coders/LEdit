#ifndef NORMAL_VIEW_H
#define NORMAL_VIEW_H

#include "document_view.h"

class NormalView : public DocumentView{
public:
	NormalView(){}
	virtual void display(int x_screen_start, int y_screen_start, char * text);
};

#endif /* NORMAL_VIEW_H */
