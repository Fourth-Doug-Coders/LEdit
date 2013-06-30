#include "document.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

static void addCharToLines(char ch,
			   vector<char> &current_line,
			   vector<vector<char> > &lines);

static void initLinesFromFileStream(vector<vector<char> > &lines, const string &filename);

Document::Document(const string &filename) {
    this->cursor_col = 0;
    this->cursor_row = 0;
    this->filename = filename;

    initLinesFromFileStream(this->lines, filename);
}

Document::~Document() {
}

void Document::save() {
    ofstream fout(filename.c_str());
    for (int row = 0; row < lines.size(); row++) {
	for (int col = 0; col < lines[row].size(); col++) 
	    fout << lines[row][col];
	if (row != lines.size()-1)
	    fout << endl;
    }
    fout << flush;
    fout.close();
}

void Document::addCharAtCursor(char ch) {
    moveCursorBackOntoLine();
    lines[cursor_row].insert(lines[cursor_row].begin() + cursor_col, ch);
    cursor_col++;
}

void Document::addNextLine() {
    moveCursorBackOntoLine();
    cursor_row++;
    lines.insert(lines.begin() + cursor_row, vector<char>());
    lines[cursor_row] = lines[cursor_row-1];
    lines[cursor_row].erase(lines[cursor_row].begin(),
			    lines[cursor_row].begin() + cursor_col);
    lines[cursor_row-1].erase(lines[cursor_row-1].begin() + cursor_col,
			      lines[cursor_row-1].end());
    cursor_col = 0;
}

void Document::moveCursorLeft() {
    moveCursorBackOntoLine();
    cursor_col--;
    if (cursor_col < 0) {
	if (cursor_row == 0) {
	    cursor_col = 0;
	} else {
	    cursor_row--;
	    cursor_col = lines[cursor_row].size();
	}
    }
}

void Document::moveCursorRight() {
    cursor_col++;
    if (cursor_col > lines[cursor_row].size()) {
	if (cursor_row == lines.size()-1) {
	    cursor_col = lines[cursor_row].size();
	} else {
	    cursor_row++;
	    cursor_col = 0;
	}
    }
}

void Document::moveCursorUp() {
    cursor_row--;
    if (cursor_row < 0)
	cursor_row = 0;
}

void Document::moveCursorDown() {
    cursor_row++;
    if (cursor_row > lines.size()-1)
    	cursor_row = lines.size()-1;
}

void Document::moveCursorBackOntoLine() {
    if (cursor_col > lines[cursor_row].size())
	cursor_col = lines[cursor_row].size();
}

int Document::getNumLines() {
    return lines.size();
}

char Document::getCharAt(int row, int col) {
    return lines[row][col];
}

int Document::getLineLength(int row) {
    return lines[row].size();
}

int Document::getCursorRow() {
    return cursor_row;
}

int Document::getCursorCol() {
    return cursor_col;
}

static void addCharToLines(char ch,
			   vector<char> &current_line,
			   vector<vector<char> > &lines) {
    if (ch == '\n') {
	lines.push_back(current_line);
	current_line.clear();
    } else {
	current_line.push_back(ch);
    }
}

static void initLinesFromFileStream(vector<vector<char> > &lines, const string &filename) {
    ifstream fin(filename.c_str());
    vector<char> current_line;

    for (char ch = fin.get(); !fin.fail(); ch = fin.get())
	addCharToLines(ch, current_line, lines);
    lines.push_back(current_line);
    
    fin.close();
}

