#include <iostream>
#include "Heap.h"
using namespace std;
template<class T, int m_size>
struct MaxHeap : public Heap<T, m_size> {
    MaxHeap() : Heap<T, m_size>()
    {
        Heap<T, m_size>::arrayType(1); //changes the array type to 1 for percolating up and down
    }
    MaxHeap(const Heap<T, m_size> &origHeap) : Heap<T, m_size>(origHeap)
    {
        Heap<T, m_size>::arrayType(1);  //same as constructor but for copied array
    }
};