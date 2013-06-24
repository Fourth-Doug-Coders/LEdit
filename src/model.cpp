#include "model.h"

Model::Model() {
    currentDoc = new Document("test.ldt");
}

Model::~Model() {
    delete currentDoc;
}

Document *Model::getCurrentDocument() {
    return currentDoc;
}
