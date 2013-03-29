#ifndef KEYSTROKE_CONTROL_H
#define KEYSTROKE_CONTROL_H

#include "keystroke.h"

class KeystrokePrint : public Keystroke {
    public:
    void log(std::ostream &out);
};

class KeystrokeQuit : public Keystroke {
    public:
    void log(std::ostream &out);
    bool shouldContinue();
};

class KeystrokeSave : public Keystroke {
    public:
    void log(std::ostream &out);
};

class KeystrokeBackspace : public Keystroke {
    public:
    void log(std::ostream &out);
};

#endif /* KEYSTROKE_CONTROL_H */
