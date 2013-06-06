#ifndef MODEL_H
#define MODEL_H

#include "document.h"

class Model {
public:
    Model();
    ~Model();
    void addCharAtCursor(char c);
    void moveCursor(int x, int y);   

    Document *getCurrentDocument();

private:
    Document *currentDoc;
};

#endif /* MODEL_H */
