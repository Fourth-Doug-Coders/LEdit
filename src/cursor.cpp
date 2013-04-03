#include "cursor.h"

Cursor::Cursor() {
    line = col = 0;
}

int Cursor::getLineNum() {
    return line;
}

int Cursor::getColNum() {
    return col;
}

void Cursor::moveUp() {
    line--;
}

void Cursor::moveDown() {
    line++;
}

void Cursor::moveLeft() {
    col--;
}

void Cursor::moveRight() {
    col++;
}

