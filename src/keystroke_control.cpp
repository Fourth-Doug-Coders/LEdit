#include "keystroke_control.h"

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

void KeystrokeNew::log(ostream &out) {
    out << "New" << endl;
}

void KeystrokeOpen::log(ostream &out) {
    out << "Open" << endl;
}

void KeystrokeClose::log(ostream &out) {
    out << "Close" << endl;
}

void KeystrokePrint::log(ostream &out) {
    out << "Print" << endl;
}

void KeystrokeAll::log(ostream &out) {
    out << "Select All" << endl;
}

void KeystrokeCut::log(ostream &out) {
    out << "Cut" << endl;
}

void KeystrokeCopy::log(ostream &out) {
    out << "Copy" << endl;
}

void KeystrokePaste::log(ostream &out) {
    out << "Paste" << endl;
}

void KeystrokeRedo::log(ostream &out) {
    out << "Redo" << endl;
}

void KeystrokeUndo::log(ostream &out) {
    out << "Undo" << endl;
}

