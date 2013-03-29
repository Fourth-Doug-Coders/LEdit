#ifndef MODEL_H
#define MODEL_H

class Model {
public:
    Model();

    Document *getCurrentDocument();

private:
    Document *currentDoc;
};

#endif /* MODEL_H */
