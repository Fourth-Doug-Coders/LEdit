#ifndef NORMAL_VIEW_H
#define NORMAL_VIEW_H

#include "document_view.h"

class NormalView : public DocumentView{
public:
	virtual void display(Document * d);
};

#endif /* NORMAL_VIEW_H */
