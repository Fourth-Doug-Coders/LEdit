#include "keystroke_printable.h"

using namespace std;

KeystrokePrintable::KeystrokePrintable(char arg_) {
    arg = arg_;
}

void KeystrokePrintable::log(ostream &out) {
    out << "Printable '" << arg << "'" << endl;
}
