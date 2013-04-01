#ifndef KEYSTROKE_H
#define KEYSTROKE_H

#include <iostream>

class Keystroke {
public:
    virtual void log(std::ostream &out) = 0;
    virtual bool shouldContinue();
};

Keystroke *getNextKeystroke();

#endif /* KEYSTROKE_H */
