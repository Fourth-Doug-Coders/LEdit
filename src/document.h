#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <list>
#include <string>
#include <vector>

class Document {
public:
    Document(const std::string &filename);
    ~Document();

    void save();

    void addCharAtCursor(char c);
    void addNextLine();

    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorUp();
    void moveCursorDown();

    int getNumLines();
    char getCharAt(int row, int col);
    int getLineLength(int row);

    int getCursorRow();
    int getCursorCol();

private:
    std::string filename;

    std::vector<std::vector<char> > lines;

    int cursor_col, cursor_row;

    void moveCursorBackOntoLine();
};

#endif /* DOCUMENT_H */
