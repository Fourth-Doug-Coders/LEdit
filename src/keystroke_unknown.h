#ifndef KEYSTROKE_UNKNOWN_H
#define KEYSTROKE_UNKNOWN_H

#include "keystroke.h"

class KeystrokeUnknown : public Keystroke {
    public:
    KeystrokeUnknown(char arg);

    void log(std::ostream &out);
    
private:
    char arg;
};

#endif /* KEYSTROKE_UNKNOWN_H */
