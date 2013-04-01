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
static const int KP_DOWN        = 258;
static const int KP_UP          = 259;
static const int KP_LEFT        = 260;
static const int KP_RIGHT       = 261;
static const int KP_HOME        = 262;
static const int KP_DELETE      = 330;
static const int KP_PAGEDOWN    = 338;
static const int KP_PAGEUP      = 339;
static const int KP_END         = 360;


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
    case KP_DELETE:       return new KeystrokeDelete();
    case KP_UP:           return new KeystrokeUp();
    case KP_DOWN:         return new KeystrokeDown();
    case KP_LEFT:         return new KeystrokeLeft();
    case KP_RIGHT:        return new KeystrokeRight();
    case KP_HOME:         return new KeystrokeHome();
    case KP_END:          return new KeystrokeEnd();
    case KP_PAGEUP:       return new KeystrokePageUp();
    case KP_PAGEDOWN:     return new KeystrokePageDown();
    default:              return new KeystrokeUnknown(nextCh);
    }

}

bool Keystroke::shouldContinue() {
    return true;
}
