#include "document.h"

#include <cstdio>
#include <fstream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Document test
#include <boost/test/unit_test.hpp>

using namespace std;

string TESTFILENAME = "testfile12345.txt";

/**
 * This method applies a series of commands presented in a string
 * to a document in the following way:
 * - Anything between []'s is added as if typed in
 * - s is save
 * - l,r,u,d are the arrow keys
 * - n is enter (newline)
 */
static void applyCommandsToDocument(Document *doc, const string &commands);

/**
 * This method uses BOOST_CHECK to check that the contents of the
 * file given by "filename" are exactly the same as the contents of
 * the string "expectedContents". If any are not, this method will
 * cause the test to fail.
 */
static void checkFullFile(const string &filename, const string &expectedContents);

BOOST_AUTO_TEST_CASE( multipleCharacters ) {
    remove(TESTFILENAME.c_str());

    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abq] s");

    checkFullFile(TESTFILENAME, "abq");
}

BOOST_AUTO_TEST_CASE( writeAfterSaveDoesNotGetStored ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] s [fghij]");

    checkFullFile(TESTFILENAME, "abcde");
}

BOOST_AUTO_TEST_CASE( leftRightCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] l [q] r [z] s");

    checkFullFile(TESTFILENAME, "aqbz");
}

BOOST_AUTO_TEST_CASE( leftRightCursorMovementOffEndOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] lllllll [cr] rrrrrrr [s] s");
    
    checkFullFile(TESTFILENAME, "crabs");
}

BOOST_AUTO_TEST_CASE( enterAtEndOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] n [yz] s");

    checkFullFile(TESTFILENAME, "ab\nyz");
}

BOOST_AUTO_TEST_CASE( enterInMiddleOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abke] llll [cr] rr n [ca] rr [s] s");

    checkFullFile(TESTFILENAME, "crab\ncakes");
}

BOOST_AUTO_TEST_CASE( upCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] u [ijk] s");

    checkFullFile(TESTFILENAME, "abcijkde\nfgh");
}

BOOST_AUTO_TEST_CASE( cursorMovesUpPastBeginning ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] uuu [ijk] s");

    checkFullFile(TESTFILENAME, "abcijkde\nfgh");
}

BOOST_AUTO_TEST_CASE( downCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fghij] u ll d [kl] s");

    checkFullFile(TESTFILENAME, "abcde\nfghklij");
}

BOOST_AUTO_TEST_CASE( cursorMovesDownPastEnd ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fghij] u ll dddd [kl] s");

    checkFullFile(TESTFILENAME, "abcde\nfghklij");
}

BOOST_AUTO_TEST_CASE( leftPastLineBreakGoesToEndOfPreviousLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abc] n [def] llll [g] ll [h] s");

    checkFullFile(TESTFILENAME, "abhcg\ndef");
}

BOOST_AUTO_TEST_CASE( rightPastLineBreakGoesToFrontOfNextLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] u rrr [ijk] s");

    checkFullFile(TESTFILENAME, "abcde\nijkfgh");
}

BOOST_AUTO_TEST_CASE( upPastTheEndOfAShorterLineDoesNotCrash ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[huging] n [a] n [car] uu [g] s");

    checkFullFile(TESTFILENAME, "hugging\na\ncar");
}

BOOST_AUTO_TEST_CASE( typePastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[hug] n [a] n [automobile] u [n] s");

    checkFullFile(TESTFILENAME, "hug\nan\nautomobile");
}

BOOST_AUTO_TEST_CASE( leftPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [a] n [blabla] u l [bl] s");

    checkFullFile(TESTFILENAME, "say\nbla\nblabla");
}

BOOST_AUTO_TEST_CASE( rightPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [bla] n [abla] u r [bl] s");

    checkFullFile(TESTFILENAME, "say\nbla\nblabla");
}

BOOST_AUTO_TEST_CASE( enterPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [a] n [blabla] u n [bla] s");

    checkFullFile(TESTFILENAME, "say\na\nbla\nblabla");
}

static void applyCommandsToDocument(Document *doc, const string &commands) {
    bool insert = false;

    for (int i = 0; i < commands.size(); i++) {
	if (!insert) {
	    switch(commands[i]) {
	    case ' ':
		break;
	    case '[':
		insert = true;
		break;
	    case 's':
		doc->save();
		break;
	    case 'n':
		doc->addNextLine();
		break;
	    case 'l':
		doc->moveCursorLeft();
		break;
	    case 'r':
		doc->moveCursorRight();
		break;
	    case 'u':
		doc->moveCursorUp();
		break;
	    case 'd':
		doc->moveCursorDown();
		break;
	    default:
		BOOST_CHECK(!"Bad command");
	    }
	} else {
	    if (commands[i] == ']')
		insert = false;
	    else
		doc->addCharAtCursor(commands[i]);
	}
    }
	
}

static void checkFullFile(const string &filename, const string &expectedContents) {
    ifstream fin(filename.c_str());

    for (int i = 0; i < expectedContents.size(); i++)
	BOOST_CHECK(fin.get() == expectedContents[i]);

    fin.get();
    BOOST_CHECK(fin.fail());

    remove(TESTFILENAME.c_str());
}
