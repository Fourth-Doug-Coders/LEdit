#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <list>
#include <vector>
#include <string>

class Cursor;

class Document {
public:
    Document();
    ~Document();

    void open(std::string filename);
    void save();
    bool isOpen();
    void addCharAtCursor(char c);
    void moveCursor(int x, int y);

    char getChar(int lineNum, int colNum);
    const std::list<char> *getLine(int lineNum);

    //gives the entire thing as a pointer
    const std::vector<std::string> getLinesAtScreen(int screen_x, int screen_y);

    int getFirstVisibleLineNum();
    int getNumLines();
    int getStartX();
    int getStartY();

    Cursor *getCursor();

private:
    // To be filled in later
    std::vector<std::list<char>*> lines;
    Cursor *cursor;
    int start_x, start_y;
};

#endif /* DOCUMENT_H */
