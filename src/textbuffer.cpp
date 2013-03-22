#include "textbuffer.h"

#include <iostream>
#include <string>

using namespace std;

void TextBuffer::put(char c, int x, int y){
    if(x > this->data.size()) this->data.resize(x + 1);
    if(y > this->data[x].size()) this->data[x].resize(y + 1);
    this->data[x][y] = c;
}

vector<char> TextBuffer::getLineAt(int x){
    if(this->data.size() < x)
        throw new int(0);
    return this->data[x];
}

// assumes x and y are valid
// this may not be true
void TextBuffer::remove(char c, int x, int y){
    this->data[x][y] = ' ';
}

// assumes x and y are valid
// this may not be true
void TextBuffer::mod(char c, int x, int y){
    this->data[x][y] = c;
}
