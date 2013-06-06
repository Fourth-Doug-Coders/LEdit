#ifndef KEYSTROKE_PRINTABLE_H
#define KEYSTROKE_PRINTABLE_H

#include "keystroke.h"
#include "model.h"

class KeystrokePrintable : public Keystroke {
public:
    KeystrokePrintable(char arg);
    void apply(Model *);
    void log(std::ostream &out);
    
private:
    char arg;
};

#endif /* KEYSTROKE_PRINTABLE_H */
