/*
 * Llama.h
 *
 *  Created on: Feb 12, 2020
 *      Author: Joseph Chieng
 */
#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {

   public:

   LlamaUnderflow(const string& what) : std::out_of_range(what) { }


} ;


template <class T, int LN_SIZE>
class Llama {

   public:

   Llama() ;
   Llama(const Llama<T,LN_SIZE>& other) ;   // copy constructor
   ~Llama() ;


   int size() ; 
   void dump() ;
   void push(const T& data) ;
   T pop() ;


   void dup() ;    //  (top) A B C D -> A A B C D
   void swap() ;   //  (top) A B C D -> B A C D 
   void rot() ;    //  (top) A B C D -> C A B D


   T peek(int offset) const ;


   // overloaded assignment operator
   //
   const Llama<T,LN_SIZE>& operator=(const Llama<T,LN_SIZE>& rhs)
   {
      LlamaNode<T, LN_SIZE> *clear = front;
      while (clear)
      {
        LlamaNode<T, LN_SIZE> *clearnext = clear->m_next;
        delete clear;
        clear = clearnext;
      }
      if (this != &rhs)
      {
         this->head = new LlamaNode<T, LN_SIZE>();
         this->cursor = this->head;
         this->front = this->head;
         int iter = 0;
         int newsize = LN_SIZE-1;
         position = rhs.front;
         while (position != nullptr)
         {
            iter++;
            if (position->m_next == nullptr)
            {
               if(position == rhs.cursor)
               {
                  newsize = rhs.csz-1;
               }
               for (int i = 0; i <= newsize; i++)
               {
                  push(position->arr[i]);
               }
            }
            position = position->m_next;
    }
    while (iter > 1)
    {
        iter--;
        newsize = LN_SIZE - 1;
        position = rhs.front;
        for(int i = 1; i < iter; i++)
        {
            position = position->m_next;
        }
        if (position == rhs.cursor)
        {
            newsize = rhs.csz -1;
        }
        if (position != rhs.cursor && position == rhs.front)
        {
            LlamaNode<T, LN_SIZE>* dummy = new LlamaNode<T, LN_SIZE>;
            dummy->m_next = front;
            front = dummy;
            dummy = nullptr;
            newsize = -10;
        }
        for (int i = 0; i <= newsize; i++)
        {
            push(position->arr[i]);
        }
    }
 }
}


   //
   // Add your public member functions & public data mebers here:
   //


   private:


   //
   // Add your private member functions & private data mebers here:
   //
   LlamaNode<T, LN_SIZE> *head = nullptr;
   LlamaNode<T, LN_SIZE> *next = nullptr;
   LlamaNode<T, LN_SIZE> *cursor = nullptr;
   LlamaNode<T, LN_SIZE> *tempcursor = nullptr;
   LlamaNode<T, LN_SIZE> *front = nullptr;
   LlamaNode<T, LN_SIZE> *position = nullptr;
   int sz = 0; //total size of all arrays
   int csz = 0; //size for the current array


} ;


#include "Llama.cpp"


#endif