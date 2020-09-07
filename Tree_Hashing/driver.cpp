/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : Joseph Chieng
 * Date   : 04-November-2014
 * Section: Lecture-02
 * E-mail:  jcc5578@tamu.edu
 *
 * HashedSplays Class implementation.
 *
 *************************************************************/
#include "HashedSplays.h"  // Includes constants

using namespace std;

int main(int argc, char *argv[]) {

    try {
        // Instatiate the main object
        int ALPHABET_SIZE = 26;
        HashedSplays wordFrequecy(ALPHABET_SIZE);
        // Build the trees
        wordFrequecy.FileReader(argv[1]);

        // Test methods to show hashed splay trees work
        wordFrequecy.PrintHashCountResults();
        wordFrequecy.PrintTree(13); // Prints the "T" tree
        wordFrequecy.PrintTree("M");
        //wordFrequecy.PrintTree("K"); // should be mpty running input1
        wordFrequecy.FindAll("salt"); // should find all the's (ignoring case)
        cout << endl;
    }
    // Error catching
    catch (Exceptions &cException) {
        cout << "EXCEPTION: " << cException.what() << endl;
        return 1;
    }
    
    //Uncomment for number of seconds running.
    //cout << clock() / (float)(CLOCKS_PER_SEC) << endl;
    return 0;
}