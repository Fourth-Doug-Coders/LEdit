#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <list>
#include <string>

class Document {
public:
    Document();

    void open(std::string filename);
    void save();
    bool isOpen();

    char getChar(int lineNum, int colNum);
    list<char> getLine(int lineNum);

    int getFirstVisibleLineNum();
    int getNumLines();

    int getCursorX();
    int getCursorY();

private:
    // To be filled in later
};

#endif /* DOCUMENT_H */
