#include "document.h"

#include "cursor.h"

#include <string>

using namespace std;

static list<char> *toList(const string &arg);

Document::Document() {
    lines.push_back(toList("This is the first line"));
    lines.push_back(toList("    This line has some spaces in"
			   " front (we'll worry about tabs later)"));
    lines.push_back(toList("The next line will be blank, just for fun."));
    lines.push_back(toList(""));
    lines.push_back(toList("Uh oh, the document is about to end!!!!"));
    lines.push_back(toList("This is the last line"));

    cursor = new Cursor();
    for (int i = 0; i < 4; i++)
	cursor->moveDown();
    for (int i = 0; i < 12; i++)
	cursor->moveRight();
}

Document::~Document() {
    for (int i = 0; i < lines.size(); i++)
	delete lines[i];

    delete cursor;
}

char Document::getChar(int lineNum, int colNum) {
    list<char>::iterator it = lines[lineNum]->begin();
    for (int i = 0; i < colNum; i++)
	it++;
    return *it;
}

const list<char> *Document::getLine(int lineNum) {
    return lines[lineNum];
}

int Document::getFirstVisibleLineNum() {
    return 0;
}

int Document::getNumLines() {
    return lines.size();
}

Cursor *Document::getCursor() {
    return cursor;
}

static list<char> *toList(const string &arg) {
    list<char> *line = new list<char>;
    for (int i = 0; i < arg.size(); i++)
	line->push_back(arg[i]);
    return line;
}

