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
    start_x = 0;
    start_y = 0;
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

void Document::addCharAtCursor(char c)
{
    //TODO: add this here
}
void Document::moveCursor(int x, int y)
{
    //TODO:add this here
}

//gives the entire thing as a pointer
const vector<string> Document::getLinesAtScreen(int screen_x, int screen_y)
{
    vector<string> lines;
    for(int i = start_y; i < start_y + screen_y; i++) {
        if(i > lines.size()) lines.push_back("");
        string appendStr = "";
        const list<char> * line = getLine(i);
        int j = 0;
        for(list<char>::const_iterator it = line->begin(); it != line->end(); it++){
            if(j < start_x || j < start_x + screen_x || j > line->size()) continue;
            appendStr.append(1u, *it);
        }
        lines.push_back(appendStr);
    }
    return lines;
}


int Document::getStartX(){
    return start_x;
}

int Document::getStartY(){
    return start_y;
}

static list<char> *toList(const string &arg) {
    list<char> *line = new list<char>;
    for (int i = 0; i < arg.size(); i++)
	line->push_back(arg[i]);
    return line;
}

