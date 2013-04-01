#include "keystroke.h"

#include "keystroke_control.h"
#include "keystroke_printable.h"
#include "keystroke_special.h"
#include "keystroke_unknown.h"

#include <cctype>
#include <curses.h>

static const int KP_ALL         = 1;
static const int KP_COPY        = 3;
static const int KP_TAB         = 9;
static const int KP_ENTER       = 10;
static const int KP_NEW         = 14;
static const int KP_OPEN        = 15;
static const int KP_PRINT       = 16;
static const int KP_QUIT        = 17;
static const int KP_SAVE        = 19;
static const int KP_PASTE       = 22;
static const int KP_CLOSE       = 23;
static const int KP_CUT         = 24;
static const int KP_REDO        = 25;
static const int KP_UNDO        = 26;
static const int KP_BACKSPACE   = 127;

Keystroke *getNextKeystroke() {
    int nextCh = getch();

    if (isprint(nextCh))
	return new KeystrokePrintable(nextCh);
    switch(nextCh) {
    case KP_ALL:          return new KeystrokeAll();
    case KP_COPY:         return new KeystrokeCopy();
    case KP_TAB:          return new KeystrokeTab();
    case KP_ENTER:        return new KeystrokeEnter();
    case KP_NEW:          return new KeystrokeNew();
    case KP_OPEN:         return new KeystrokeOpen();
    case KP_PRINT:        return new KeystrokePrint();
    case KP_QUIT:         return new KeystrokeQuit();
    case KP_SAVE:         return new KeystrokeSave();
    case KP_PASTE:        return new KeystrokePaste();
    case KP_CLOSE:        return new KeystrokeClose();
    case KP_CUT:          return new KeystrokeCut();
    case KP_REDO:         return new KeystrokeRedo();
    case KP_UNDO:         return new KeystrokeUndo();
    case KP_BACKSPACE:    return new KeystrokeBackspace();
    default:              return new KeystrokeUnknown(nextCh);
    }

}

bool Keystroke::shouldContinue() {
    return true;
}
