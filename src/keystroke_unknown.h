#ifndef KEYSTROKE_UNKNOWN_H
#define KEYSTROKE_UNKNOWN_H

#include "keystroke.h"

class KeystrokeUnknown : public Keystroke {
    public:
    KeystrokeUnknown(int arg);

    void log(std::ostream &out);
    
private:
    int arg;
};

#endif /* KEYSTROKE_UNKNOWN_H */
