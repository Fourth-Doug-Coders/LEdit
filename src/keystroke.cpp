#include "keystroke.h"

#include "keystroke_printable.h"
#include "keystroke_special.h"
#include "keystroke_unknown.h"

#include <cctype>
#include <curses.h>

static const int KP_PRINT       = 16;
static const int KP_QUIT        = 17;
static const int KP_SAVE        = 19;
static const int KP_BACKSPACE   = 127;

Keystroke *getNextKeystroke() {
    int nextCh = getch();

    if (isprint(nextCh)) {
	return new KeystrokePrintable(nextCh);
    } else if (nextCh == KP_PRINT) {
	return new KeystrokePrint();
    } else if (nextCh == KP_QUIT) {
	return new KeystrokeQuit();
    } else if (nextCh == KP_SAVE) {
	return new KeystrokeSave();
    } else if (nextCh == KP_BACKSPACE) {
	return new KeystrokeBackspace();
    } else {
	return new KeystrokeUnknown(nextCh);
    }
}

bool Keystroke::shouldContinue() {
    return true;
}
