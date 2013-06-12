#ifndef NORMAL_VIEW_H
#define NORMAL_VIEW_H

#include <vector>
#include <string>
#include "document_view.h"

class NormalView : public DocumentView{
public:
	NormalView(){}
	virtual void display(const std::vector<std::string> & text, int x_screen_start, int y_screen_start);
};

#endif /* NORMAL_VIEW_H */
