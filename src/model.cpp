#include "model.h"

Model::Model() {
    currentDoc = new Document();
}

Model::~Model() {
    delete currentDoc;
}

Document *Model::getCurrentDocument() {
    return currentDoc;
}

void Model::addCharAtCursor(char c){
	currentDoc->addCharAtCursor(c);
}

void Model::moveCursor(int x, int y){
	currentDoc->moveCursor(x, y);
}

