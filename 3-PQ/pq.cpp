//===========================================================================================
// Colin Smith and Emma Steinman
// pq.cpp
// This file contains the methods for the Min Priority Queue templated class
//===========================================================================================


using namespace std;

//===========================================================================================
// MinPriorityQueue()
// default constructor
// Parameters: N/A
// Return Value: N/A
// Pre-Conditions: N/A
// Post-Conditions: A new minimum priority queue exists
//===========================================================================================

template <class KeyType>
    MinPriorityQueue<KeyType>::MinPriorityQueue ( void ) : MinHeap<KeyType>::MinHeap() {}
    
//===========================================================================================
// MinPriorityQueue(int n)
// default constructor with size
// Parameters: 
// 		int n- size of Priority Queue to be created
// Return Value: N/A
// Pre-Conditions: N/A
// Post-Conditions: A new minimum priority queue of size n exists
//===========================================================================================

template <class KeyType>
    MinPriorityQueue<KeyType>::MinPriorityQueue ( int n ) : MinHeap<KeyType>::MinHeap(n) {}
    
//===========================================================================================
// MinPriorityQueue(const MinPriorityQueue<KeyType>& pq)
// copy constructor
// Parameters: 
//		MinPriorityQueue<KeyType> &pq - Existing priority queue to be copied
// Return Value: N/A
// Pre-Conditions: N/A
// Post-Conditions: A new minimum priority queue with the same elements as pq exists
//===========================================================================================

template <class KeyType>
    MinPriorityQueue<KeyType>::MinPriorityQueue (const MinPriorityQueue<KeyType>& pq)
{
		this->copy(pq);
}

//===========================================================================================
// minimum()
// returns minimum value
// Parameters: N/A
// Return Value: 
//		A[0] - the first value in the priority queue which will be the smallest
// Pre-Conditions: 
//		Calling object must be a minimum priority queue
// Post-Conditions:
//		The priority queue will remain unchanged, only returning the value
//===========================================================================================
 
template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::minimum ( void ) const
{
		return A[0];
}
//===========================================================================================
// extractMin()
// removes and returns minimum value
// Parameters: N/A
// Return Value: 
//		A[heapSize] - The smallest value in the priority queue before it was swapped and 
//					  heapSize was decremented
// Pre-Conditions: 
//		Calling object must be a minimum priority queue or empty
// Post-Conditions:
//		heapSize will be one less (if not originally empty) and will be a minimum priority 
//		queue
//===========================================================================================
    
template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::extractMin ( void )
{
	if(!empty())
	{
		swap(0,heapSize-1);							//swaps smallest value to end of pq
		heapSize--;
		heapify(0);
		return A[heapSize];							//returns smallest value
	}
	else
	{
		return NULL;								//returns NULL if pq is empty
	}
}
//===========================================================================================
// decreaseKey(int index, KeyType* key)
// decreases the key of the given index to the given key
// Parameters: 
//		int index 		- the index to be decreased
//		KeyType* key 	- the new key to be assigned
// Return Value: N/A
// Pre-Conditions:
//		The calling object must be a priority queue
// Post-Conditions:
//		The key of the given index (in the original pq) will be decreased and the calling 
//		object will be a minimum priority queue
//===========================================================================================
    
template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey	(int index, KeyType* key)
{
		if(*key > *A[index])
		{
			throw KeyError();						//index is out of bounds
			
		}else{
			A[index] = key;
			while(index > 0 && *A[index] < *A[parent(index)])
			{
				swap(index, parent(index));			//swaps index with its parent
				index = parent(index);				
			}
		}
}
//===========================================================================================
// insert(KeyType* key)
// inserts the given key into the minimum priority queue
// Parameters: 
//		KeyType* key - the key to be inserted into the min priority queue
// Return Value: N/A
// Pre-Conditions:
//		The calling object must be a minimum priority queue
// Post-Conditions:
//		The minimum priority queue will now contain the given key and be a minimum priority
//		queue
//===========================================================================================
    
template <class KeyType>
void MinPriorityQueue<KeyType>::insert (KeyType* key)
{
	if(heapSize == capacity)
	{
		throw FullError();							//if heap is full
	}else{
		heapSize++;
		A[heapSize - 1] = key;						//inserts key at end of array
		decreaseKey(heapSize - 1, key);				//sorts key into correct place
	}
	
	//sorted[heapSize] = key;
	//heapSize++;
	//this->heapSort(sorted);
}
//===========================================================================================
// empty()
// returns a boolean value indicating if the minimum priority queue is empty
// Parameters: N/A
// Return Value: 
//		(heapSize == 0) - a boolean value indicating if the heapSize is 0 or not, i.e. if 
//					      the priority queue is empty (heapSize == 0) or not (heapSize != 0)
// Pre-Conditions:
//		The calling object must be a minimum priority queue
// Post-Conditions:
//		The minimum priority queue will remain unchanged
//===========================================================================================
    
template <class KeyType>
bool MinPriorityQueue<KeyType>::empty ( void ) const
{
	return (heapSize == 0);
}
//===========================================================================================
// length()
// returns the length of the minimum priority queue
// Parameters: N/A
// Return Value: 
//		heapSize - the length of the heap which is the length of the priority queue
// Pre-Conditions:
//		The calling object must be a minimum priority queue
// Post-Conditions:
//		The minimum priority queue will remain unchanged
//===========================================================================================
    
template <class KeyType>
int MinPriorityQueue<KeyType>::length ( void ) const
{
	return heapSize;
}
//===========================================================================================
// toString()
// turns a minimum priorty queue into a string to be used in cout
// Parameters: N/A
// Return Value: 
//		ss.str() - The values of the minimum priority queue in a string format 
// Pre-Conditions:
//		The calling object must be a minimum priority queue
// Post-Conditions:
//		The calling object will remain unchanged
//===========================================================================================

template <class KeyType>
string MinPriorityQueue<KeyType>::toString ( void ) const
{
	stringstream ss;
	
	if (heapSize == 0)
	{
		ss << "[ ]";
	}
	else
	{
		ss << "[";
		for (int index = 0; index < heapSize - 1; index++)
			ss << *(A[index]) << ", ";
		ss << *(A[heapSize - 1]) << "]";
	}
	return ss.str();
}
