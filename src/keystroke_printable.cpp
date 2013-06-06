#include "keystroke_printable.h"

using namespace std;

KeystrokePrintable::KeystrokePrintable(char arg_) {
    arg = arg_;
}

void KeystrokePrintable::apply(Model * m) {
	//um... we sure want Model here? what about document?
	m->addCharAtCursor(arg);
}

void KeystrokePrintable::log(ostream &out) {
    out << "Printable '" << arg << "'" << endl;
}
