#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <list>
#include <string>
#include <vector>

class Document {
public:
    Document();
    ~Document();

    void open(std::string filename);
    void save();
    bool isOpen();

    char getChar(int lineNum, int colNum);
    const std::list<char> *getLine(int lineNum);

    int getFirstVisibleLineNum();
    int getNumLines();

    int getCursorX();
    int getCursorY();

private:
    // To be filled in later
    std::vector<std::list<char>*> lines;
};

#endif /* DOCUMENT_H */
