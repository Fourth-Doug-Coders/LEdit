#include "model.h"

Model::Model() {
    currentDoc = new Document;
}

Model::~Model() {
    delete currentDoc;
}

Document *Model::getCurrentDocument() {
    return currentDoc;
}
