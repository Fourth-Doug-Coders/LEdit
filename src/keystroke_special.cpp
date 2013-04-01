#include "keystroke_special.h"

using namespace std;

void KeystrokeEnter::log(ostream &out) {
    out << "Enter" << endl;
}

void KeystrokeTab::log(ostream &out) {
    out << "Tab" << endl;
}

void KeystrokeBackspace::log(ostream &out) {
    out << "Backspace" << endl;
}

void KeystrokeDelete::log(ostream &out) {
    out << "Delete" << endl;
}

void KeystrokeUp::log(ostream &out) {
    out << "Up" << endl;
}

void KeystrokeDown::log(ostream &out) {
    out << "Down" << endl;
}

void KeystrokeLeft::log(ostream &out) {
    out << "Left" << endl;
}

void KeystrokeRight::log(ostream &out) {
    out << "Right" << endl;
}

void KeystrokeHome::log(ostream &out) {
    out << "Home" << endl;
}

void KeystrokeEnd::log(ostream &out) {
    out << "End" << endl;
}

void KeystrokePageUp::log(ostream &out) {
    out << "PageUp" << endl;
}

void KeystrokePageDown::log(ostream &out) {
    out << "PageDown" << endl;
}
