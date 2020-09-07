/*****************************************
** File:    AugmentedBinarySearchTree.h
** Project: CSCE 221 Project 2
** Author:  ???
** Date:    ???
** Section: ???
** E-mail:  ???
**
**  C++ file:
**	Breif Description of the file
**
**	
**
*******************************************/

using namespace std;

#ifndef AUGMENTED_BINARY_SEARCH_TREE_H
#define AUGMENTED_BINARY_SEARCH_TREE_H


/*---------------Imported Libraries---------------*/
#include <fstream>
#include <sstream>
#include <iostream>       // For NULL
#include <queue>


/*----------------Includes---------------------*/

#include "Exceptions.h"
//#include "BinarySearchTree.h"
//#include "Proj3Aux.h"

// Binary node and forward declaration because g++ does
// not understand nested classes.
template <class Comparable>
class AugmentedBinarySearchTree;
template <class Comparable>
class BinarySearchTree;

#ifndef BINARY_NODE
#define BINARY_NODE
template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;
    int m_size;

	BinaryNode(const Comparable & theElement = -1, BinaryNode *lt = NULL, BinaryNode *rt = NULL, int size = -1)
		: element(theElement), left(lt), right(rt), m_size(size)  { }
	friend class AugmentedBinarySearchTree<Comparable>;
	friend class BinarySearchTree<Comparable>;

};
#endif // BINARY_NODE

template <class Comparable>
class AugmentedBinarySearchTree
{
public:
	/*------------Constructors/Destructors-------------*/

	explicit AugmentedBinarySearchTree();
	AugmentedBinarySearchTree(const AugmentedBinarySearchTree<Comparable> & rhs);
	~AugmentedBinarySearchTree();


	/*--------------Facilitators------------------------*/

	int remove(const Comparable & x);
	bool IsPerfect();
	bool IsComplete();
	void PrintLevels(int numlevels);
	void makeEmpty();

	/*---------------Getters---------------------------*/
	
	int RemoveResidue(); /* Assume RemoveResidue will always be called after Print */
	const Comparable & NthElement(int n);
	int Rank(const Comparable & x);
	const Comparable & Median();
	BinaryNode<Comparable> * findMin(BinaryNode<Comparable> *t) const;

	
	/*---------------Setters---------------------------*/

	int insert(const Comparable & x);

private:

	int insert(const Comparable & x, BinaryNode<Comparable> * & t) const; 
	int remove(const Comparable & x, BinaryNode<Comparable> * & t) const; 
	void PrintLevels(queue <BinaryNode<Comparable> *> q, int levels);
	void RemoveResidue(BinaryNode<Comparable> * & t, int *deletions) const;
	BinaryNode<Comparable> * NthElement(BinaryNode<Comparable> *t, int *nodesVisited, int n) const;
	void Rank(const Comparable & x, BinaryNode<Comparable> *t, int *nodesVisited) const;
	bool IsPerfect(queue <BinaryNode<Comparable> *> q, int height);
	void makeEmpty(BinaryNode<Comparable> * & t) const;
	bool IsComplete(queue <BinaryNode<Comparable>*> q, int height);  //<-- Extra Credit!

	/*------------------Members-----------------------------*/
	//BinarySearchTree<Comparable> m_tree;
	BinaryNode<Comparable> *root;
	BinaryNode<Comparable> *ret = new BinaryNode<Comparable>(); // used in order to create a separate node that returns -1 on exception.
};

#include "AugmentedBinarySearchTree.cpp"
#endif // AUGMENTED_BINARY_SEARCH_TREE_H 