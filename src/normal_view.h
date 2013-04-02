#ifndef NORMAL_VIEW_H
#define NORMAL_VIEW_H

#include "document_view.h"
#include <iostream>

class NormalView::DocumentView {
public:
	virtual void display() = 0;
};

#endif /* NORMAL_VIEW_H */
