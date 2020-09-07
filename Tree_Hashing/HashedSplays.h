/*****************************************
** File:    HashedSplays.h
** Project: CSCE 221 Project 3
** Author:  Joseph Chieng
** Date:    4/8/2020
** Section: 518
** E-mail:  jcc5578@tamu.edu
**
** 
**
*******************************************/
#ifndef HASHED_SPLAYS
#define HASHED_SPLAYS
#include <iostream>
#include <fstream>
#include <vector>
#include "SplayTree.h"
using namespace std;

class HashedSplays {
    public:
    HashedSplays(int size)
    {
       for(int i = 0; i < size; i++)
       {
           table.push_back(SplayTree<Node>());
       }
       m_trees = size;
    }
    ~HashedSplays()
    {
        for(int i = 0; i < m_trees; i++)
        {
            table.at(i).makeEmpty();
        }
        //table = nullptr;
        
    }
    void FileReader(string inFileName)
    {
        ifstream inFile;
        inFile.open(inFileName);
        if (inFile.is_open()) {
            string word, line;
            cout << "Building hashed splay..." << endl;
            //reads through the file word by word, and removes any symbols that are not letters.
            while (inFile >> word)
            { 
                //gets rid of all symbols through ascii from the front
                while(int(word[0]) > 122 || int(word[0]) < 65 || int(word[0] > 90 && int(word[0] < 97)))
                {   
                    word = word.substr(1);
                    if(word.length() == 0)
                        break;
                }
                //gets rid of all symbols through ascii from the back
                while(int(word[word.length()-1]) > 122 || int(word[word.length()-1]) < 65 || int(word[word.length()-1] > 90 && int(word[word.length()-1] < 97)))
                {
                    word = word.substr(0, word.length()-1);
                    if(word.length()==0)
                        break;
                }
                //places word in specific index based on first letter
                if (word[0] == 'A' || word[0] == 'a')
                {
                    table.at(0).insert(Node(word,1));
                }
                else if (word[0] == 'B' || word[0] == 'b')
                {
                    table.at(1).insert(Node(word,1));
                }
                else if (word[0] == 'C' || word[0] == 'c')
                {
                    table.at(2).insert(Node(word,1));
                }
                else if (word[0] == 'D' || word[0] == 'd')
                {
                    table.at(3).insert(Node(word,1));
                }
                else if (word[0] == 'E' || word[0] == 'e')
                {
                    table.at(4).insert(Node(word,1));
                }
                else if (word[0] == 'F' || word[0] == 'f')
                {
                    table.at(5).insert(Node(word,1));
                }
                else if (word[0] == 'G' || word[0] == 'g')
                {
                    table.at(6).insert(Node(word,1));
                }
                else if (word[0] == 'H' || word[0] == 'h')
                {
                    table.at(7).insert(Node(word,1));
                }
                else if (word[0] == 'I' || word[0] == 'i')
                {
                    table.at(8).insert(Node(word,1));
                }
                else if (word[0] == 'J' || word[0] == 'j')
                {
                    table.at(9).insert(Node(word,1));
                }
                else if (word[0] == 'K' || word[0] == 'k')
                {
                    table.at(10).insert(Node(word,1));
                }
                else if (word[0] == 'L' || word[0] == 'l')
                {
                    table.at(11).insert(Node(word,1));
                }
                else if (word[0] == 'M' || word[0] == 'm')
                {
                    table.at(12).insert(Node(word,1));
                }
                else if (word[0] == 'N' || word[0] == 'n')
                {
                    table.at(13).insert(Node(word,1));
                }
                else if (word[0] == 'O' || word[0] == 'o')
                {
                    table.at(14).insert(Node(word,1));
                }
                else if (word[0] == 'P' || word[0] == 'p')
                {
                    table.at(15).insert(Node(word,1));
                }
                else if (word[0] == 'Q' || word[0] == 'q')
                {
                    table.at(16).insert(Node(word,1));
                }
                else if (word[0] == 'R' || word[0] == 'r')
                {
                    table.at(17).insert(Node(word,1));
                }
                else if (word[0] == 'S' || word[0] == 's')
                {
                    table.at(18).insert(Node(word,1));
                }
                else if (word[0] == 'T' || word[0] == 't')
                {
                    table.at(19).insert(Node(word,1));
                }
                else if (word[0] == 'U' || word[0] == 'u')
                {
                    table.at(20).insert(Node(word,1));
                }
                else if (word[0] == 'V' || word[0] == 'v')
                {
                    table.at(21).insert(Node(word,1));
                }
                else if (word[0] == 'W' || word[0] == 'w')
                {
                    table.at(22).insert(Node(word,1));
                }
                else if (word[0] == 'X' || word[0] == 'x')
                {
                    table.at(23).insert(Node(word,1));
                }
                else if (word[0] == 'Y' || word[0] == 'y')
                {
                    table.at(24).insert(Node(word,1));
                }
                else if (word[0] == 'Z' || word[0] == 'z')
                {
                    table.at(25).insert(Node(word,1));
                }
                else
                {
                    continue; //if it doesn't start with a letter, and somehow got through the nonalphabet filter, ignore it
                }
                

            }
            inFile.close();
        }
        else // checks if the file exists in the same directory
        {
            cout << "File could not be opened" << endl;
            file_exists = false;
        }
        
    }
    void PrintTree(int index)
    {
        if (file_exists == true) {
            if (index < m_trees)
                table.at(index).printTree(); //prints the splay tree at index as long as the index exists
            else {
                try {
                    throw (ArrayIndexOutOfBoundsException());
                }
                catch (exception const & ex) {
                    cerr << ex.what() << "The index should only be from zero to twenty-five. " << endl;
                }
            }
        }
    }
    void PrintTree(string letter)
    {
        //Prints the splay tree at an index determined by the letter string
        if (file_exists == true) {
            if (letter == "A" || letter == "a")
            {
                table.at(0).printTree();
            }
            else if (letter == "B" || letter == "b")
            {
                table.at(1).printTree();
            }
            else if (letter == "C" || letter == "c")
            {
            table.at(2).printTree();
            }
            else if (letter == "D" || letter == "d")
            {
                table.at(3).printTree();
            }
            else if (letter == "E" || letter == "e")
            {
                table.at(4).printTree();
            }
            else if (letter == "F" || letter == "f")
            {
                table.at(5).printTree();
            }
            else if (letter == "G" || letter == "g")
            {
                table.at(6).printTree();
            }
            else if (letter == "H" || letter == "h")
            {
                table.at(7).printTree();
            }
            else if (letter == "I" || letter == "i")
            {
                table.at(8).printTree();
            }
            else if (letter == "J" || letter == "j")
            {
                table.at(9).printTree();
            }
            else if (letter == "K" || letter == "k")
            {
            table.at(10).printTree();
            }
            else if (letter == "L" || letter == "l")
            {
                table.at(11).printTree();
            }
            else if (letter == "M" || letter == "m")
            {
            table.at(12).printTree();
            }
            else if (letter == "N" || letter == "n")
            {
                table.at(13).printTree();
            }
            else if (letter == "O" || letter == "o")
            {
                table.at(14).printTree();
            }
            else if (letter == "P" || letter == "p")
            {
                table.at(15).printTree();
            }
            else if (letter == "Q" || letter == "q")
            {
                table.at(16).printTree();
            }
            else if (letter == "R" || letter == "r")
            {
                table.at(17).printTree();
            }
            else if (letter == "S" || letter == "s")
            {
                table.at(18).printTree();
            }
            else if (letter == "T" || letter == "t")
            {
                table.at(19).printTree();
            }
            else if (letter == "U" || letter == "u")
            {
                table.at(20).printTree();
            }
            else if (letter == "V" || letter == "v")
            {
                table.at(21).printTree();
            }
            else if (letter == "W" || letter == "w")
            {
                table.at(22).printTree();
            }
            else if (letter == "X" || letter == "x")
            {
                table.at(23).printTree();
            }
            else if (letter == "Y" || letter == "y")
            {
                table.at(24).printTree();
            }
            else if (letter == "Z" || letter == "z")
            {
            table.at(25).printTree();
            }
            else
            {
                try {
                    throw (IteratorOutOfBoundsException());
                }
                catch (std::exception const & ex) {
                    cerr << ex.what() << "That is not a letter in the English Alphabet " << endl;
                }
            }
        }
    }
    void PrintHashCountResults()
    {
        //prints the root node at every index
        if (file_exists == true) {
            for (int i = 0; i < m_trees; i++)
            {
                table.at(i).printRoot();
            }
        }
    }
    void FindAll(string inPart)
    {
        //Checks the first letter of the string to determine which index, and correspondingly, which splay tree to check
        if (file_exists == true) {
            cout << "Printing the results of nodes that start with '" << inPart << "'" << endl; 
                if (inPart[0] == 'A' || inPart[0] == 'a')
                {
                    table.at(0).printFilter(inPart);
                }
                else if (inPart[0] == 'B' || inPart[0] == 'b')
                {
                    table.at(1).printFilter(inPart);
                }
                else if (inPart[0] == 'C' || inPart[0] == 'c')
                {
                    table.at(2).printFilter(inPart);
                }
                else if (inPart[0] == 'D' || inPart[0] == 'd')
                {
                    table.at(3).printFilter(inPart);
                }
                else if (inPart[0] == 'E' || inPart[0] == 'e')
                {
                    
                    table.at(4).printFilter(inPart);
                }
                else if (inPart[0] == 'F' || inPart[0] == 'f')
                {
                    
                    table.at(5).printFilter(inPart);
                }
                else if (inPart[0] == 'G' || inPart[0] == 'g')
                {
                    
                    table.at(6).printFilter(inPart);
                }
                else if (inPart[0] == 'H' || inPart[0] == 'h')
                {
                    
                    table.at(7).printFilter(inPart);
                }
                else if (inPart[0] == 'I' || inPart[0] == 'i')
                {
                    
                    table.at(8).printFilter(inPart);
                }
                else if (inPart[0] == 'J' || inPart[0] == 'j')
                {
                    
                    table.at(9).printFilter(inPart);
                }
                else if (inPart[0] == 'K' || inPart[0] == 'k')
                {
                    
                    table.at(10).printFilter(inPart);
                }
                else if (inPart[0] == 'L' || inPart[0] == 'l')
                {
                    
                    table.at(11).printFilter(inPart);
                }
                else if (inPart[0] == 'M' || inPart[0] == 'm')
                {
                    
                    table.at(12).printFilter(inPart);
                }
                else if (inPart[0] == 'N' || inPart[0] == 'n')
                {
                    
                    table.at(13).printFilter(inPart);
                }
                else if (inPart[0] == 'O' || inPart[0] == 'o')
                {
                    
                    table.at(14).printFilter(inPart);
                }
                else if (inPart[0] == 'P' || inPart[0] == 'p')
                {
                    
                    table.at(15).printFilter(inPart);
                }
                else if (inPart[0] == 'Q' || inPart[0] == 'q')
                {
                    
                    table.at(16).printFilter(inPart);
                }
                else if (inPart[0] == 'R' || inPart[0] == 'r')
                {
                    
                    table.at(17).printFilter(inPart);
                }
                else if (inPart[0] == 'S' || inPart[0] == 's')
                {
                    
                    table.at(18).printFilter(inPart);
                }
                else if (inPart[0] == 'T' || inPart[0] == 't')
                {
                    table.at(19).printFilter(inPart);
                }
                else if (inPart[0] == 'U' || inPart[0] == 'u')
                {
                    
                    table.at(20).printFilter(inPart);
                }
                else if (inPart[0] == 'V' || inPart[0] == 'v')
                {
                    
                    table.at(21).printFilter(inPart);
                }
                else if (inPart[0] == 'W' || inPart[0] == 'w')
                {
                    
                    table.at(22).printFilter(inPart);
                }
                else if (inPart[0] == 'X' || inPart[0] == 'x')
                {
                    
                    table.at(23).printFilter(inPart);
                }
                else if (inPart[0] == 'Y' || inPart[0] == 'y')
                {
                    
                    table.at(24).printFilter(inPart);
                }
                else if (inPart[0] == 'Z' || inPart[0] == 'z')
                {
                    
                    table.at(25).printFilter(inPart);
                }
                else
                {
                    cout << "Does not start with a letter" << endl;
                }
                
        }
    }

    private:
        vector <SplayTree<Node>> table;
        int m_trees;
        bool file_exists = true;


};

#endif