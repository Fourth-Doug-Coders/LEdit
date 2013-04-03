#ifndef CURSOR_H
#define CURSOR_H

class Document;

class Cursor {
public:
    Cursor();

    int getLineNum();
    int getColNum();
    
    friend class Document;
    
protected:
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    
private:
    int line, col;
};

#endif /* CURSOR_H */
