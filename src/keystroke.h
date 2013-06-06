#ifndef KEYSTROKE_H
#define KEYSTROKE_H

#include <iostream>
#include "model.h"

class Keystroke {
public:
    virtual void log(std::ostream &out) = 0;
    virtual bool shouldContinue();
    virtual void apply(Model *){}
};

Keystroke *getNextKeystroke();

#endif /* KEYSTROKE_H */
