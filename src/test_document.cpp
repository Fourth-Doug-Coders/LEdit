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

/**
 * This method uses BOOST_CHECK to check that the contents of the
 * Document provided are the same as the array of strings, and that
 * the number of lines is correct. If any of the lines are incorrect,
 * this method will cause the test to fail.
 */
static void checkFullDocument(Document *doc, int numLines, string *lines);

static void checkCursorPosition(Document *doc, int row, int col) {
    BOOST_CHECK(doc->getCursorRow() == row);
    BOOST_CHECK(doc->getCursorCol() == col);
}

BOOST_AUTO_TEST_CASE( emptyDocumentHasOneEmptyLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);

    string lines[] = {""};
    checkFullDocument(document, 1, lines);
    checkCursorPosition(document, 0, 0);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( multipleCharacters ) {
    remove(TESTFILENAME.c_str());

    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abq] s");

    string lines[] = {"abq"};

    checkFullDocument(document, 1, lines);
    checkFullFile(TESTFILENAME, "abq");
    checkCursorPosition(document, 0, 3);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( writeAfterSaveDoesNotGetStored ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] s [fghij]");

    string lines[] = {"abcdefghij"};

    checkFullDocument(document, 1, lines);
    checkFullFile(TESTFILENAME, "abcde");
    checkCursorPosition(document, 0, 10);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( leftRightCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] l [q] r [z] s");

    string lines[] = {"aqbz"};

    checkFullDocument(document, 1, lines);
    checkFullFile(TESTFILENAME, "aqbz");
    checkCursorPosition(document, 0, 4);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( leftRightCursorMovementOffEndOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] lllllll [r] rrrrrrr [s] llllll [c] s");
    
    string lines[] = {"crabs"};

    checkFullDocument(document, 1, lines);
    checkFullFile(TESTFILENAME, "crabs");
    checkCursorPosition(document, 0, 1);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( enterAtEndOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[ab] n [yz] s");

    string lines[] = {
	"ab",
	"yz"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "ab\nyz");
    checkCursorPosition(document, 1, 2);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( enterInMiddleOfLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abke] llll [cr] rr n [ca] rr [s] s");

    string lines[] = {
	"crab",
	"cakes"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "crab\ncakes");
    checkCursorPosition(document, 1, 5);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( upCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] u [ijk] s");

    string lines[] = {
	"abcijkde",
	"fgh"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abcijkde\nfgh");
    checkCursorPosition(document, 0, 6);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( cursorMovesUpPastBeginning ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] uuu [ijk] s");

    string lines[] = {
	"abcijkde",
	"fgh"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abcijkde\nfgh");
    checkCursorPosition(document, 0, 6);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( downCursorMovement ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fghij] u ll d [kl] s");

    string lines[] = {
	"abcde",
	"fghklij"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abcde\nfghklij");
    checkCursorPosition(document, 1, 5);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( cursorMovesDownPastEnd ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fghij] u ll dddd [kl] s");

    string lines[] = {
	"abcde",
	"fghklij"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abcde\nfghklij");
    checkCursorPosition(document, 1, 5);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( leftPastLineBreakGoesToEndOfPreviousLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abc] n [def] llll [g] ll [h] s");

    string lines[] = {
	"abhcg",
	"def"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abhcg\ndef");
    checkCursorPosition(document, 0, 3);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( rightPastLineBreakGoesToFrontOfNextLine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[abcde] n [fgh] u rrr [ijk] s");

    string lines[] = {
	"abcde",
	"ijkfgh"
    };

    checkFullDocument(document, 2, lines);
    checkFullFile(TESTFILENAME, "abcde\nijkfgh");
    checkCursorPosition(document, 1, 3);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( upPastTheEndOfAShorterLineDoesNotCrash ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[huging] n [a] n [car] uu [g] s");

    string lines[] = {
	"hugging",
	"a",
	"car"
    };

    checkFullDocument(document, 3, lines);
    checkFullFile(TESTFILENAME, "hugging\na\ncar");
    checkCursorPosition(document, 0, 4);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( typePastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[hug] n [a] n [automobile] u [n] s");

    string lines[] = {
	"hug",
	"an",
	"automobile"
    };

    checkFullDocument(document, 3, lines);
    checkFullFile(TESTFILENAME, "hug\nan\nautomobile");
    checkCursorPosition(document, 1, 2);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( leftPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [a] n [blabla] u l [bl] s");
    
    string lines[] = {
	"say",
	"bla",
	"blabla"
    };

    checkFullDocument(document, 3, lines);
    checkFullFile(TESTFILENAME, "say\nbla\nblabla");
    checkCursorPosition(document, 1, 2);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( rightPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [bla] n [abla] u r [bl] s");

    string lines[] = {
	"say",
	"bla",
	"blabla"
    };

    checkFullDocument(document, 3, lines);
    checkFullFile(TESTFILENAME, "say\nbla\nblabla");
    checkCursorPosition(document, 2, 2);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( enterPastTheEndOfALine ) {
    remove(TESTFILENAME.c_str());
    
    Document *document = new Document(TESTFILENAME);
    applyCommandsToDocument(document, "[say] n [a] n [blabla] u n [bla] s");

    string lines[] = {
	"say",
	"a",
	"bla",
	"blabla"
    };

    checkFullDocument(document, 4, lines);
    checkFullFile(TESTFILENAME, "say\na\nbla\nblabla");
    checkCursorPosition(document, 2, 3);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( oneLineFileIsLoadedCorrectly ) {
    remove(TESTFILENAME.c_str());

    ofstream fout(TESTFILENAME.c_str());
    fout << "Test File is loaded correctly?" << flush;
    fout.close();

    Document *document = new Document(TESTFILENAME);
    
    string lines[] = {
	"Test File is loaded correctly?"
    };
    checkFullDocument(document, 1, lines);
    checkCursorPosition(document, 0, 0);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( oneLineWithNewlineAtEndIsLoadedCorrectly ) {
    remove(TESTFILENAME.c_str());

    ofstream fout(TESTFILENAME.c_str());
    fout << "Test File is loaded correctly?" << endl;
    fout.close();

    Document *document = new Document(TESTFILENAME);
    
    string lines[] = {
	"Test File is loaded correctly?",
	""
    };
    checkFullDocument(document, 2, lines);
    checkCursorPosition(document, 0, 0);

    remove(TESTFILENAME.c_str());
}

BOOST_AUTO_TEST_CASE( fileIsLoadedCorrectly ) {
    remove(TESTFILENAME.c_str());

    ofstream fout(TESTFILENAME.c_str());
    fout << "Test\nfile\nReading correctly?" << endl;
    fout.close();

    Document *document = new Document(TESTFILENAME);
    
    string lines[] = {
	"Test",
	"file",
	"Reading correctly?",
	""
    };
    checkFullDocument(document, 4, lines);
    checkCursorPosition(document, 0, 0);

    remove(TESTFILENAME.c_str());
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
}

static void checkFullDocument(Document *doc, int numLines, string *lines) {
    BOOST_REQUIRE(doc->getNumLines() == numLines);
    for (int row = 0; row < numLines; row++) {
	BOOST_REQUIRE(doc->getLineLength(row) == lines[row].size());
	for (int col = 0; col < lines[row].size(); col++)
	    BOOST_CHECK(doc->getCharAt(row, col) == lines[row][col]);
    }
}
