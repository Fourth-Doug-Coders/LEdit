#ifndef KEYSTROKE_SPECIAL_H
#define KEYSTROKE_SPECIAL_H

#include "keystroke.h"

class KeystrokeEnter : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeTab : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeBackspace : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeDelete : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeUp : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeDown : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeLeft : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeRight : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeHome : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokeEnd : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokePageUp : public Keystroke {
public:
    void log(std::ostream &out);
};

class KeystrokePageDown : public Keystroke {
public:
    void log(std::ostream &out);
};

#endif /* KEYSTROKE_SPECIAL_H */
