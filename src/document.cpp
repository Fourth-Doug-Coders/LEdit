#include "document.h"

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
}

Document::~Document() {
    for (int i = 0; i < lines.size(); i++)
	delete lines[i];
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

int Document::getCursorX() {
    return 4;
}

int Document::getCursorY() {
    return 12;
}

static list<char> *toList(const string &arg) {
    list<char> *line = new list<char>;
    for (int i = 0; i < arg.size(); i++)
	line->push_back(arg[i]);
    return line;
}

