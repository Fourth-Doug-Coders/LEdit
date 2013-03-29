#include "keystroke_unknown.h"

using namespace std;

KeystrokeUnknown::KeystrokeUnknown(char arg_) {
    arg = arg_;
}

void KeystrokeUnknown::log(ostream &out) {
    out << "Unknown '" << (int)arg << "'" << endl;
}
