#ifndef HEAP_H_
#define HEAP_H_
#include "PinHit.h"
template<class T, int m_size> class Heap{

	public:

		// required functions by UML
		Heap();
		Heap(const Heap<T, m_size>& origHeap);
		bool Contains(const T& needle) const;	
		const T* Find(const T& needle) const;
		T& Remove();	
		void Insert(T& insertable);		
		void PercolateUp(int index);
		void PercolateDown(int index);
		// student-made functions below
		void arrayType(int type);
		void printArray();
		~Heap();
	private:

		// UML-required member variables
		T* m_array;

		// student-made member variables
		int size;
		int csize;
		int whichType = 0; //1 means max, -1 means min, 0 means neither

};

#include "Heap.cpp"
#include "MaxValueHeap.h"
#include "MinValueHeap.h"
#endif /* HEAP_H_ */