//============================================================
// Emma Steinman
// March 24, 2017
// List.cc
// Class methods for List class.
//============================================================

#include <iostream>
#include <stdlib.h>
#include <string>

//============================================================
// default constructor
//============================================================
template <class T>
		List<T>::List	(void)
{
	array = new T[DEFAULT_LIST_SIZE];
	capacity = DEFAULT_LIST_SIZE;
	size = 0;
}

//============================================================
// copy constructor
// copies a list from an existing list
//============================================================
template <class T>
		List<T>::List	(const List<T> &c)
{
	array = new T[c.capacity];		//creates new array
	capacity = c.capacity;
	size = c.size;						//changes size/cap
	for (int i = 0; i < size; i++)
		array[i] = c.array[i];			//copies items over

}

//============================================================
// isEmpty
// tests if list is empty and returns boolean value
//============================================================
template <class T>
bool	List<T>::isEmpty	(void)
{
	return (size == 0);
}

//============================================================
// length
// returns number of items in list
//============================================================
template <class T>
int		List<T>::length	(void) const
{
	return size;
}

//============================================================
// operator []
// returns item in list at indicated index
//============================================================
template <class T>
T&		List<T>::operator[]	(int i)
{
	if (i >= size or i < 0)
	{
		//cout << "Error. Invalid index\n";
		//exit(1);
		throw IndexError();
	}
	return array[i];
}


//============================================================
// toString
// converts list to string
//============================================================
template <class T>
string	List<T>::toString		(void) const
{
	string s;

	for (int i = 0; i < size; i++)
	{									//converts each values
		s += to_string(array[i]);		//to string and appends
		s += " ";
	}
	return s;
}

//============================================================
// append
// adds item to the end of list
//============================================================
template <class T>
void	List<T>::append		(T c)
{
	if (size + 1 > capacity)			//checks capacity
	{									//creates new pointer
		T *oldArray = array;			//to existing array
		capacity *= 2;
		array = new T[capacity];		//creates new array

		for (int i = 0; i < size; i++)
			array[i] = oldArray[i];		//copies existing values

		array[size] = c;				//copies last value
		size += 1;
		delete[] oldArray;				//deletes original array
	}
	else
		array[size] = c;
		size += 1;

}

//============================================================
// insert
// inserts indicated item at indicated position
//============================================================
template <class T>
void	List<T>::insert		(T item, int pos)
{
	if (pos > size or pos < 0)
	{
		//cout << "Error. Invalid index.\n";
		//exit(1);
		throw IndexError();
	}
	else if (size + 1 > capacity)
	{
		T *oldArray = array;
		capacity *= 2;
		array = new T[capacity];

		for (int i = 0; i < pos; i++)
			array[i] = oldArray[i];

		array[pos] = item;

		for (int i = pos; i < size; i++)
			array[i+1] = oldArray[i];

		size += 1;
		delete[] oldArray;
	}
	else
	{
		T *oldArray = array;
		array = new T[capacity];

		for (int i = 0; i < pos; i++)
			array[i] = oldArray[i];

		array[pos] = item;

		for (int i = pos; i < size; i++)
			array[i+1] = oldArray[i];

		size += 1;
		delete[] oldArray;
	}


}

//============================================================
// remove
// removes item from list at indicated position
//============================================================
template <class T>
void	List<T>::remove		(int pos)
{
	if (pos >= size or pos < 0)
	{
		//cout << "Error. Invalid index.\n";
		//exit(1);
		throw IndexError();
	}
	T *oldArray = array;
	array = new T[capacity];

	for (int i = 0; i < pos; i ++)
		array[i] = oldArray[i];

	for (int i = pos; i < size; i++)
		array[i] = oldArray[i+1];

	size -= 1;
	delete[] oldArray;
}

//============================================================
// operator +
// concatenates two lists into a third list
//============================================================
template <class T>
List<T>	List<T>::operator+		(const List<T> c) const
{
	List<T> l;									//creates empty list


	for (int i = 0; i < size; i++)			//appends values from
		l.append(array[i]);					//first list

	for	(int i = 0; i < c.size; i++)		//appends values from
		l.append(c.array[i]);				//second list

	return l;
}

//============================================================
// operator =
// assigns values in a list to another list
//============================================================
template <class T>
List<T>	List<T>::operator=		(List<T> c) const
{
	List<T> l;
	l.capacity = c.capacity;

	for (int i = 0; i < size; i++)
		l.append(c.array[i]);

	return l;
}

//============================================================
// clear
// removes items from list
//============================================================
template <class T>
void	List<T>::clear			(void)
{
	T *oldArray = array;
	array = new T[capacity];
	size = 0;
	delete[] oldArray;
}

//============================================================
// destructor
// deletes list and clears the memory
//============================================================
template <class T>
		List<T>::~List			(void)
{
	delete[] array;
}
