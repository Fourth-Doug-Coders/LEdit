#include "keystroke_special.h"

using namespace std;

void KeystrokeQuit::log(ostream &out) {
    out << "Quit" << endl;
}

bool KeystrokeQuit::shouldContinue() {
    return false;
}

void KeystrokeSave::log(ostream &out) {
    out << "Save" << endl;
}

void KeystrokePrint::log(ostream &out) {
    out << "Print" << endl;
}

void KeystrokeBackspace::log(ostream &out) {
    out << "Backspace" << endl;
}
