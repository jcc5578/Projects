#ifndef HEAP_CPP_
#define HEAP_CPP_
#include <iostream>
#include "Heap.h"
	template<class T, int m_size>
	Heap<T, m_size>::Heap() {
        m_array = new T[m_size];
		size = m_size;
		csize = 0;
	}
	template<class T, int m_size>
	Heap<T, m_size>::~Heap() 
	{
		delete m_array;
		m_array = nullptr;
	}
	template<class T, int m_size>
	Heap<T, m_size>::Heap(const Heap<T, m_size>& origHeap) {
		m_array = new T[m_size];
		this->whichType = origHeap.whichType; //sets type and csize to be equal to original heap
		this->csize = origHeap.csize;
		for (int i = 0; i <= origHeap.csize; i++)
		{
			m_array[i] = origHeap.m_array[i];
		}
	}

	template<class T, int m_size>
	bool Heap<T, m_size>::Contains(const T& needle) const {
		for(int i = 0; i < size; i++)
		{
			if (m_array[i] == needle) //checks if needle is in the array
			{
				return true;
			}
		}
		return false;
	}	


	template<class T, int m_size>
	const T* Heap<T, m_size>::Find(const T& needle) const {
		for(int i = 0; i < size; i++)
		{
			if (m_array[i] == needle)
			{
				return &m_array[i]; //returns index value if needle is in array
			}
		}
		return nullptr;
	}

	template<class T, int m_size>
	T& Heap<T, m_size>::Remove() {
		if(csize <= 0) //if nothing in array, can't remove
		{
			std::cout << "Cannot remove as no nodes available" << std::endl;
			return m_array[0];
		}
		else
		{
			T& former = m_array[1];
			m_array[1] = m_array[csize];
			PercolateDown(1);
			return former;
		}
		
	}

	template<class T, int m_size>
	void Heap<T, m_size>::Insert(T& insertable) {
		csize++;
		m_array[csize] = insertable; //increases csize by 1, inserts node at next index point, and percolates up accordingly
		PercolateUp(csize);
	}	

	template<class T, int m_size>
	void Heap<T, m_size>::PercolateUp(int index) {
		int hole = csize;
		T sub = m_array[index];
		if(whichType == 1) //max heap
		{
			for(; hole >= 1 && sub.CompareTo(m_array[hole/2]) > 0 && hole/2 != 0; hole/=2)
			{
				m_array[hole] = m_array[hole/2]; //switches parent and child
			}
			m_array[hole] = sub; //index hole now holds newly inserted position
		}
		else if(whichType == -1) //min heap
		{
			for(; hole >= 1 && sub.CompareTo(m_array[hole/2]) < 0 && hole/2 != 0; hole/=2)
			{
				m_array[hole] = m_array[hole/2]; //switches parent and child
			}
			m_array[hole] = sub; //index hole now holds newly inserted position
		}
		else{
			std::cout << "Did not specify if min or max heap" << std::endl;
		}
	}

	template<class T, int m_size>
	void Heap<T, m_size>::PercolateDown(int index) {
		int child;
		T sub = m_array[index];
		if(whichType == -1) //min heap
		{
			for(; index*2 <= csize; index = child)
			{
				child = index*2;
				if(child != csize && m_array[child+1].CompareTo(m_array[child]) < 0) //switches children if right child is smaller
					child++;
				if(m_array[child].CompareTo(sub) < 0)
					{
						m_array[index] = m_array[child]; //switches child and parent if parent is larger
					}
				else
				{
					break;
				}
				
			}
			
		}
		else if (whichType == 1) //max heap
		{
			for(; index*2 <= csize; index = child)
			{
				child = index*2;
				if(child != csize && m_array[child+1].CompareTo(m_array[child]) > 0) //switches children if right child is larger
					child++;
				if(m_array[child].CompareTo(sub) > 0)
					{
						m_array[index] = m_array[child]; //switches child and parent if parent is smaller
					}
				else
				{
					break;
				}
				
			}
		}
		m_array[index] = sub; //sets index to be the sub
		csize--; //removes one csize to adjust for deletion
		
	}
	template<class T, int m_size>
	void Heap<T, m_size>::arrayType(int type)
	{
		whichType = type; //simply determines max or min heap
	}
	template<class T, int m_size>
	void Heap<T, m_size>::printArray() //used to print the array; only for check heap
	{
		std::cout << "--------------------------------------------------------\n";
		for (int i = 1; i <= csize; i++) {
			std::cout << m_array[i].GetKey() << " | " << m_array[i].GetValue() << " | " << i << std::endl;
		}
	}

#endif /* HEAP_CPP_ */