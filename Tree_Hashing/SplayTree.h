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
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "dsexceptions.h"
#include "Node.h"
#include <iostream>        // For NULL
using namespace std;

// SplayTree class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class SplayTree
{
  public:
  int counter;
  int splaycount;
    SplayTree( )
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }

    SplayTree( const SplayTree & rhs )
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        *this = rhs;
    }

    ~SplayTree( )
    {
        makeEmpty( );
        delete nullNode;
    }

    /**
     * Find the smallest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     smaller than any item in the tree, then call findMin.
     * Return the smallest item or throw UnderflowException if empty.
     */
    const Comparable & findMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->left != nullNode )
            ptr = ptr->left;

        splay( ptr->element, root );
        return ptr->element;
    }

    /**
     * Find the largest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     larger than any item in the tree, then call findMax.
     * Return the largest item or throw UnderflowException if empty.
     */
    const Comparable & findMax( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->right != nullNode )
            ptr = ptr->right;

        splay( ptr->element, root );
        return ptr->element;
    }


    bool contains( const Comparable & x )
    {
        if( isEmpty( ) )
            return false;
        splay( x, root );
        return root->element == x;
    }

    bool isEmpty( ) const
    {
        return root == nullNode;
    }
    //bootstrap for printing the root of the tree
    void printRoot() const
    {
        if(isEmpty( ) )
            cout << "This tree has no nodes" << endl;
        else
        {
            printRoot(root);
        }
    }
    //bootstrap for inserting, in order to not allow the ability to change the root
    void insert( const Comparable & x )
    {
        insert(x, root);
    }
    //bootstrap for printAll(called printFilter in my case)
    void printFilter(string filter) const
    {
        if(isEmpty( ) )
            cout << "This tree has no nodes" << endl;
        else
        {
            printFilter(root, filter);
        }
    }
    //bootstrap for printTree, which also couts the number of splays
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
        cout << "This tree has had " << splaycount << " splays." << endl;  
    }

    void makeEmpty( )
    {
    /******************************
     * Comment this out, because it is prone to excessive
     * recursion on degenerate trees. Use alternate algorithm.
        
        reclaimMemory( root );
        root = nullNode;
     *******************************/
        while( !isEmpty( ) )
        {
            findMax( );        // Splay max item to root
            remove( root->element );
        }
    }

    void remove( const Comparable & x )
    {
        BinaryNode *newTree;

            // If x is found, it will be at the root
        if( !contains( x ) )
            return;   // Item not found; do nothing

        if( root->left == nullNode )
            newTree = root->right;
        else
        {
            // Find the maximum in the left subtree
            // Splay it to the root; and then attach right child
            newTree = root->left;
            splay( x, newTree );
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

    const SplayTree & operator=( const SplayTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }

        return *this;
    }

private:
    struct BinaryNode
    {
        Comparable  element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( ) : left( NULL ), right( NULL ) { }
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element( theElement ), left( lt ), right( rt ) { }
    };

    BinaryNode *root;
    BinaryNode *nullNode;

    /**
     * Internal method to reclaim internal nodes in subtree t.
     * WARNING: This is prone to running out of stack space.
     */
    void reclaimMemory( BinaryNode * t )
    {
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }
    void insert( const Comparable & x ,  BinaryNode * & temp)
    {
        static BinaryNode *newNode = NULL;

        if( newNode == NULL )
            newNode = new BinaryNode;
        newNode->element = x;

        if( temp == nullNode )
        {
            newNode->left = newNode->right = nullNode;
            temp = newNode;
        }
        else
        {
            splay( x, temp );
            if( x < temp->element )
            {
                newNode->left = temp->left;
                newNode->right = temp;
                temp->left = nullNode;
                temp = newNode;
            }
            else
            if( temp->element < x )
            {
                newNode->right = temp->right;
                newNode->left = temp;
                temp->right = nullNode;
                temp = newNode;
            }
            else
                return;
        }
        counter++;
        newNode = NULL;   // So next insert will call new
    }
    //Prints only the root
    void printRoot( BinaryNode *t ) const
    {
        cout << "This tree starts with " << t->element << " and has " << counter << " nodes" << endl;
    }
    //the printAll function(printFilter in my case) is done in inorder format, similar to printTree. While the example given used preorder,
    //there were no instructions stating that it must be done in preorder, so I kept it as inorder, to keep it in parallel to printTree
    void printFilter(BinaryNode *t, string filter) const
    {
        Node* filt = (Node*)&t->element;
        //turns the node into a string
        string word = filt->GetWord();
        word = Util::Lower(word); //lower case word
        filter = Util::Lower(filter); //lower case the "filtered" string
        if (t != t->left)
        {
            printFilter(t->left, filter);
            if(word.find(filter, 0) == 0) //checks if the word starts with the "filtered" string, and cout if it does
            {
                cout << t->element << endl;
            }
            printFilter(t->right, filter);

        }
        filt = nullptr;

    }
    /**
     * Internal method to print a subtree t in sorted order.
     * WARNING: This is prone to running out of stack space.
     */
   void printTree( BinaryNode *t ) const
    {
        if( t != t->left )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     */
    BinaryNode * clone( BinaryNode * t ) const
    {
        if( t == t->left )  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }

        // Tree manipulations
    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    /**
     * Internal method to perform a top-down splay.
     * The last accessed node becomes the new root.
     * This method may be overridden to use a different
     * splaying algorithm, however, the splay tree code
     * depends on the accessed item going to the root.
     * x is the target item to splay around.
     * t is the root of the subtree to splay.
     */
    void splay( const Comparable & x, BinaryNode * & t )
    {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;   // Guarantee a match
        Node* pointX = (Node*)&x;
        Node* pointT;
        for( ; ; )
        {
            pointT = (Node*)&t->element;
            if( x < t->element )
            {
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                if( t->left == nullNode )
                    break;
                // Link Right
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if( t->element < x )
            {
                if( t->right->element < x )
                    rotateWithRightChild( t );
                if( t->right == nullNode )
                    break;
                // Link Left
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            //increases frequency if the word already exists
            else {
                if (pointT->GetWord() == pointX->GetWord())
                {
                    pointT->IncrementFrequency();
                }
                break;
            }
        }
        splaycount++; //keeps track of number of splays
        pointX = nullptr;
        pointT = nullptr;
        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }
};

#endif