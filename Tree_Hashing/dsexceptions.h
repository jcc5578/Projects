/*****************************************
** File:    dsexceptions.h
** Project: CSCE 221 Project 3
** Author:  Joseph Chieng
** Date:    4/8/2020
** Section: 518
** E-mail:  jcc5578@tamu.edu
**
**  Exceptions to be thrown
**
*******************************************/
#ifndef DS_EXCEPTIONS
#define DS_EXCEPTIONS

#include <iostream>
#include <exception>
using namespace std;

class Exceptions {

    public:
        Exceptions(string message) {
            mess = message;
        }
        string what()
        {
            return mess;
        }
    
    private:
        string mess;
};
class UnderflowException : public exception {
    virtual const char* what() const throw() {
        return "Underflow Exception: ";
    }

};

class IllegalArgumentException : public exception {
    virtual const char* what() const throw() {
        return "Illegal Argument Exception: ";
    }
};

class ArrayIndexOutOfBoundsException : public exception {
    virtual const char* what() const throw() {
        return "Array Index out of bounds Exception: ";
    }
};

class IteratorOutOfBoundsException : public exception {
    virtual const char* what() const throw() {
        return "iterator out of bounds exception: ";
    }
};

class IteratorMismatchException : public exception {
    virtual const char* what() const throw() {
        return "iterator mismatch exception: ";
    }
};

class IteratorUninitializedException : public exception {
    virtual const char* what() const throw() {
        return "iterator uninitialized exception: ";
    }
};

#endif