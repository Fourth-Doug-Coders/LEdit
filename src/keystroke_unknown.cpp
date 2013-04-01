#include "keystroke_unknown.h"

using namespace std;

KeystrokeUnknown::KeystrokeUnknown(int arg_) {
    arg = arg_;
}

void KeystrokeUnknown::log(ostream &out) {
    out << "Unknown '" << arg << "'" << endl;
}
