/*
 * Llama.cpp
 *
 *  Created on: Feb 12, 2020
 *      Author: Joseph Chieng
 */
#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_
#include <iostream>
#include "Llama.h"

template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama()
{
    head = new LlamaNode<T, LN_SIZE>();
    cursor = head;
    front = head;
}
template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T, LN_SIZE>& other)
{
    this->head = new LlamaNode<T, LN_SIZE>();
    this->cursor = this->head;
    this->front = this->head;
    int iter = 0;
    int newsize = LN_SIZE-1;
    position = other.front;
    //looks for the bottom node as well as the number of nodes in the Llama Stack.
    while (position != nullptr)
    {
        iter++;
        if (position->m_next == nullptr)
        {
            if(position == other.cursor)
            {
                newsize = other.csz-1;
            }
            for (int i = 0; i <= newsize; i++)
            {
                push(position->arr[i]);
            }
        }
        position = position->m_next;
    }
    //Deep copies all the nodes from the original stack to a new stack.
    while (iter > 1)
    {
        iter--;
        newsize = LN_SIZE - 1;
        position = other.front;
        //Determines which node is needed
        for(int i = 1; i < iter; i++)
        {
            position = position->m_next;
        }
        //Changes the newsize iteration to csz if it's the top node.
        if (position == other.cursor)
        {
            newsize = other.csz -1;
        }
        //Creates a dummy node to act as an empty node if there exists one in the original Llama Stack.
        if (position != other.cursor && position == other.front)
        {
            LlamaNode<T, LN_SIZE>* dummy = new LlamaNode<T, LN_SIZE>;
            dummy->m_next = front;
            front = dummy;
            dummy = nullptr;
            newsize = -10;
        }
        //Iterates all of the data from the original stack to respective positions in the copied stack.
        for (int i = 0; i <= newsize; i++)
        {
            push(position->arr[i]);
        }
    }

}
template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama()
{
    //Grabs a variable 'clear' set to the top of the stack and iterates through the stack to delete all nodes.
    LlamaNode<T, LN_SIZE> *clear = front;
    //Sets all pointers to nullptr.
    head = nullptr;
    next = nullptr;
    cursor = nullptr;
    front = nullptr;
    tempcursor = nullptr;
    position = nullptr;
    while (clear)
    {
        LlamaNode<T, LN_SIZE> *clearnext = clear->m_next;
        delete clear;
        clear = clearnext;
    }
}
template<class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size()
{
    return sz;
}
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump()
{   
    LlamaNode<T, LN_SIZE> *temp = cursor;
    cerr << "***** Llama Stack Dump ******" << endl;
    cerr << "LN_SIZE = " << LN_SIZE << endl;
    cerr << "# of items in the stack = " << sz << endl;
    front->report();
    cerr << endl;
    //Returns either message if front is not equal to cursor, which means that there is an empty node where front is pointing to.
    if (front != cursor)
    {
        cerr << "This stack has an extra node: " << front << endl;
    }
    else
    {
        cerr << "This stack does not have an extra node. " << endl;
    }
    // Displays the node address. 
    cerr << "-----  " << cursor << " -----" << endl;
    //Iterates through the top node and displays elements.
    for (int i = csz-1; i >= 0; i--)
    {
        cerr << cursor->arr[i] << endl;
    }
    //Iterates through rest of the nodes, which are completely full, and displays elements.
    while (cursor->m_next != nullptr)
    {
        cursor=cursor->m_next;
        cerr << "-----  " << cursor << " -----" << endl;
        for (int j = LN_SIZE-1; j >= 0; j--)
        {
            cerr << cursor->arr[j]  << endl;
        }
    }
    //sets cursor back to original position before dumping.
    cursor = temp;
    temp = nullptr;
}
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data)
{
    //Creates a new node if current node is filled up and points the new node to the current node before inserting data.
    if (csz == LN_SIZE && front == cursor)
    {
        next = new LlamaNode<T, LN_SIZE>();
        next->m_next = front;
        cursor = next;
        front = next;
        next = nullptr;
        csz = 0;
        cursor->arr[csz] = data;
        csz++;
        sz++;
    }
    //Inserts data into an node that was previously emptied due to pop when current node is filled.
    else if (csz == LN_SIZE && front != cursor)
    {
        cursor = front;
        csz = 0;
        cursor->arr[csz] = data;
        csz++;
        sz++;
    }
    //Inserts data into current node when not filled up.
    else
    {
        cursor->arr[csz] = data;
        csz++;
        sz++;
    }
}

template<class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop()
{
    //throws LlamaUnderflow exception if popping empty stack.
    if (csz == 0 && cursor->m_next == nullptr)
    { 
       throw LlamaUnderflow("Popping Empty Stack");
    }
    else
    {
        csz--;
        sz--;
        //Deletes empty top node when size of current node(node cursor is pointing to) is half of max.
        if (csz <= LN_SIZE/2 && front->m_next == cursor)
        {
            front->m_next = nullptr;
            delete front;
            front = cursor;
        }
        T ans = cursor->arr[csz];
        //Moves cursor to next node when top node becomes empty
        if (csz == 0 && cursor->m_next != nullptr)
        {
            cursor=cursor->m_next;
            csz = LN_SIZE;
        }
        return ans;
    }
}

template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup()
{
    //duplicates top element and pushes into stack.
    T val = cursor->arr[csz-1];
    push(val);
}

template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap()
{
    tempcursor = cursor;
    //Swaps top 2 elements if they are in the same node.
    if (csz >= 2)
    {
        T val1 = cursor->arr[csz-1];
        T val2 = cursor->arr[csz-2];
        cursor->arr[csz-2] = val1;
        cursor->arr[csz-1] = val2;
    }
    //Swaps top 2 elements if they are in different node(ie. top node only has 1 element in it)
    else 
    {
        T val1 = front->arr[csz-1];
        cursor = cursor->m_next;
        T val2 = cursor->arr[LN_SIZE-1];
        front->arr[csz-1] = val2;
        cursor->arr[LN_SIZE-1] = val1;
    }
    cursor = front;
}

template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot()
{
    //If all the elements are in the same node.
    if (csz >= 3)
    {
        T val1 = cursor->arr[csz-1];
        T val2 = cursor->arr[csz-2];
        T val3 = cursor->arr[csz-3];
        cursor->arr[csz-1] = val3;
        cursor->arr[csz-2] = val1;
        cursor->arr[csz-3] = val2;
    }
    //If there are 2 elements in the front node, and rotating between the 2 elements and the first element of the next node.
    else if (csz == 2)
    {
        T val1 = front->arr[csz-1];
        T val2 = front->arr[csz-2];
        cursor = cursor->m_next;
        T val3 = cursor->arr[LN_SIZE-1];
        front->arr[csz-1] = val3;
        front->arr[csz-2] = val1;
        cursor->arr[LN_SIZE-1] = val2;
        cursor = front;
    }
    //If there is 1 element in the front node and 2 more in the next node that needs to be rotated
    else
    {
        T val1 = front->arr[0];
        cursor = cursor->m_next;
        T val2 = cursor->arr[LN_SIZE-1];
        T val3 = cursor->arr[LN_SIZE-2];
        front->arr[0] = val3;
        cursor->arr[LN_SIZE-1] = val1;
        cursor->arr[LN_SIZE-2] = val2;
        cursor = front;
    }
    

}

template<class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const
{
    LlamaNode<T, LN_SIZE> * pkcursor = cursor;
    int szchk = csz-1;
    //Locates offset location by subtracting offset every iteration until offset becomes 0 and then returning the data at that position.
    while ((pkcursor != nullptr) && (offset >= 0))
    {
        for(int i = szchk; i >=0; i--)
        {
            if (offset == 0)
            {
                return pkcursor->arr[i];
            }
            offset--;
        }
        pkcursor = pkcursor->m_next;
        szchk = LN_SIZE-1;

    }
}
#endif