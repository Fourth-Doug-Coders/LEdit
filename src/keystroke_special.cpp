#include "keystroke_special.h"

using namespace std;

void KeystrokeEnter::log(ostream &out) {
    out << "Enter" << endl;
}

void KeystrokeBackspace::log(ostream &out) {
    out << "Backspace" << endl;
}

void KeystrokeTab::log(ostream &out) {
    out << "Tab" << endl;
}
