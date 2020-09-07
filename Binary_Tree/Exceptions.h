/*****************************************
** File:    Exceptions.h
** Project: CSCE 221 Project 2
** Author:  Joseph Chieng
** Date:    3/4/2020
** Section: 518
** E-mail:  jcc5578@tamu.edu
**
**  Exceptions to be thrown
**
*******************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
using namespace std;

struct ItemNotFound : public exception {
	virtual const char* what() const throw() {
		return "ITEM NOT FOUND EXCEPTION: ";
	}
};

struct CommandNotFound : public exception {
	virtual const char* what() const throw() {
		return "INVALID COMMAND EXCEPTION: ";
	}
};

struct NodeNotFound : public exception {
	virtual const char* what() const throw() {
		return "NODE NOT FOUND EXCEPTION: ";
	}
};

struct ArgumentNotFound : public exception {
	virtual const char* what() const throw() {
		return "INVALID ARGUMENT EXCEPTION: ";
	}
};

struct ArgumentIsNull : public exception {
	virtual const char* what() const throw() {
		return "NULL ARGUMENT EXCEPTION: ";
	}
};

#endif