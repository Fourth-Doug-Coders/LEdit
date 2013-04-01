#ifndef KEYSTROKE_SPECIAL_H
#define KEYSTROKE_SPECIAL_H

#include "keystroke.h"

class KeystrokeEnter : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeBackspace : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeTab : public Keystroke {
public:
    void log(std::ostream &out);
};

#endif /* KEYSTROKE_SPECIAL_H */
