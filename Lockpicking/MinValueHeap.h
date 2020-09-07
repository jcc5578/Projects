#include <iostream>
#include "Heap.h"
using namespace std;
template<class T, int m_size>
struct MinHeap : public Heap<T, m_size> {
    MinHeap() : Heap<T, m_size>()
    {
        Heap<T, m_size>::arrayType(-1); //changes the array type to -1 for percolating up and down
    }
    MinHeap(const Heap<T, m_size> &origHeap) : Heap<T, m_size>(origHeap)
    {
        Heap<T, m_size>::arrayType(-1); //same as constructor but for copied array
    }
};