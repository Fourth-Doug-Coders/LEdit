#include "tbuffer.h"
#include <iostream>
#include <string>

using namespace std;

void buffer::put(char c, int x, int y){
    if(x > this.buffer.size()) this.buffer.resize(x + 1);
    if(y > this.buffer[x].size()) this.buffer[x].resize(y + 1):
    this.buffer[x][y] = c;
}

string buffer::getLineAt(int x){
    if(this.buffer.size() < x) return "";
    return this.buffer[x];
}

// assumes x and y are valid
// this may not be true
void buffer::remove(char c, int x, int y){
    this.buffer[x][y] = " ";
}

// assumes x and y are valid
// this may not be true
void buffer::mod(char c, int x, int y){
    this.buffer[x][y] = c;
}
