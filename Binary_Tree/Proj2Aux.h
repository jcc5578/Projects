/******************************************
** File:    Proj2Aux.h
** Project: CSCE 221 Project 2
** Author:  Joseph Chieng
** Date:    3/4/2020
** Section: 518
** E-mail:  jcc5578@tamu.edu
**
**  C++ file:
**	Brief Description of the file
**  
**	
**
*******************************************/
#ifndef PROJ_2_AUX_H
#define PROJ_2_AUX_H

#include <iostream>
#include <fstream>
#include "AugmentedBinarySearchTree.h"
using namespace std;

class Proj2Aux {
    public:
        Proj2Aux()
        {
        }
        ~Proj2Aux()
        {
            m_tree.makeEmpty();
        }
        void DoPrintCommand(string command, int depth)
        {
            cout << command << " " << depth << ":" << endl;
            m_tree.PrintLevels(depth);
            cout << endl;
        }
        int DoRemoveCommand(string command, int element)
        {
            int x = m_tree.remove(element);
            cout << command << " " << element << ": ";
            if (x == 1)
            {
                cout << "SUCCESS" << endl;
            }
            else
            {
                cout << "FAILED" << endl;
            }
            cout << endl;
            return x;
        }
        int GetMedianCommand(string command)
        {
            int x = m_tree.Median();
            cout << command << ": ";
            if( x != -1)
                {
                    cout << x << endl;
                }
            else 
            {
                cout << "-1" << endl;
            }
            cout << endl;
            return x;
        }
        int GetNthElementCommand(string command, int nthElement)
        {
            int x = m_tree.NthElement(nthElement);
            cout << command << " " << nthElement << ": ";
            cout << x << endl;
            cout << endl;
            return x;
        }
        int GetRankCommand(string command, int element)
        {
            int x = m_tree.Rank(element);
            cout << command << " " << element << ": ";
            cout << x << endl;
            cout << endl;
            return x;
        }
        int GetResidualsCommand(string command)
        {
            int x = m_tree.RemoveResidue();
            cout << command << ": ";
            cout << x << endl;
            cout << endl;
            return x;
        }
        bool IsComplete(string command)
        {
            bool x = m_tree.IsComplete();
            cout << command << ": ";
            if(x==true)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
            cout << endl;
            return x;
        }
        bool IsPerfect(string command)
        {
            bool x = m_tree.IsPerfect();
            cout << command << ": ";
            if(x==true)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
            cout << endl;
            return x;
        }
        int ReadFromCommandFile(char* commandFile)
        {

            inFile.open(commandFile); //checks if file is in directory
            if (!inFile.is_open())
            {
                //cout << "NOT OPENED" << endl;
                return 0;
            }
            string choice, choice2;
            int num, line;
            while (getline(inFile, choice))
            {
                line = choice.find(" "); //look if there is 2nd parameter
                if (choice.find("#") != string::npos || choice.length() == 1)
                {
                    continue;
                }
                else {
                    if (choice.find(" ") != string::npos)
                    {
                        choice2 = choice.substr(line+1); //creates new variable for 2nd parameter
                        choice = choice.substr(0, choice.length()-choice2.length()-1); //changes variable for 1st parameter
                        num = stoi(choice2);
                    }
                    else
                    {
                        if (!inFile.eof()) // checks if last line
                        {
                            choice = choice.substr(0, choice.length()-1); //gets rid of \n if it exists
                        }
                        else
                        {
                            choice = choice.substr(0, choice.length());
                        }
                        
                        choice2 = " "; //sets variable to nothing if there is no 2nd parameter
                    }
                    if (choice == "MEDIAN")
                    {
                        GetMedianCommand(choice);
                    }
                    else if(choice == "RANK")
                    {
                        GetRankCommand(choice, num);
                    }
                    else if (choice == "NTH")
                    {
                        GetNthElementCommand(choice, num);
                    }
                    else if (choice == "RESIDUALS")
                    {
                        GetResidualsCommand(choice);
                    }
                    else if (choice == "PRINT")
                    {
                        DoPrintCommand(choice, num);
                    }
                    else if (choice == "REMOVE")
                    {
                        DoRemoveCommand(choice, num);
                    }
                    else if (choice == "PERFECT")
                    {
                        IsPerfect(choice);
                    }
                    else if (choice == "COMPLETE")
                    {
                        IsComplete(choice);
                    }
                    else
                    {
                        try {
                            throw CommandNotFound();
                         }
                        catch (std::exception const & ex) {
                            std::cerr << ex.what() << choice << " is not a valid command" << '\n' << endl;
                        }
                    }
                    
                }
            }
            inFile.close();
            return 1;

        }
        int ReadFromInputFile(char* inputFile)
        {
            inFile.open(inputFile);
            if (!inFile.is_open())
            {
                return 0;
            }
            string node;
            int cnode; //converted node
            while (inFile >> node)
            {
                if (!node.empty())
                {
                    cnode = stoi(node);
                    m_tree.insert(cnode);
                }
            }
            inFile.close();
            return 1;
        }
    private:
        AugmentedBinarySearchTree<int> m_tree;
        ifstream inFile;

};
#endif