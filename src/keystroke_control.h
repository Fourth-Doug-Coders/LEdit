#ifndef KEYSTROKE_CONTROL_H
#define KEYSTROKE_CONTROL_H

#include "keystroke.h"

class KeystrokeQuit : public Keystroke {
public:
    void log(std::ostream &out);
    bool shouldContinue();
};

class KeystrokeSave : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeNew : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeOpen : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeClose : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokePrint : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeAll : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeCut : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeCopy : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokePaste : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeRedo : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeUndo : public Keystroke {
public:
    void log(std::ostream &out);
};

#endif /* KEYSTROKE_CONTROL_H */
