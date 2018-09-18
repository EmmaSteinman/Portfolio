//=====================================================================
//Hannah Kerr & Emma Steinman
//April 19, 2017
//List.h
//Header file for linked list class
//=====================================================================

#include <iostream>
#include <sstream>
using namespace std;

#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
private:
	struct Node
	{
  		T     data;
  		Node *  next;
	};

	Node *head;

public:
	 					List        	(void);  				//default constructor
        		List        	(const List<T> &src);   //copy constructor
        		~List       	(void);   				//destructor
  T&   			operator[] 		(int x);
  List<T>  	operator+   	(const List<T> &l);
  List<T>  	operator=   	(const List<T> &src);
  bool  		isEmpty     	(void);
  int   		length      	(void);
  string 		toString   		(void);
  void  		append      	(T x);
  void  		insert      	(T i, int p);
  void  		remove      	(int p);
  void  		clear       	(void);

  friend ostream & operator<< ( ostream &os, List<T> &l)
  {
  	Node *ptr = l.head;
  	while (ptr != NULL)
  	{
    	os << ptr->data << " ";
    	ptr = ptr->next;
  	}
  	return os;
  }

};
class IndexError { };
#endif

//----------------------------------------------------------------------------------------
//default constructor
//creates an empty list
//----------------------------------------------------------------------------------------
template <class T>
	List<T>::List (void)
{
	head = NULL;
}

//----------------------------------------------------------------------------------------
//copy constructor
//creates a new list by copying another
//----------------------------------------------------------------------------------------
template <class T>
	List<T>::List (const List<T> &src)
{
	head = NULL;
	Node *ptr = src.head;
	while (ptr != NULL)
	{
		append(ptr->data);			//appends values to list
		ptr = ptr->next;
	}
}

//----------------------------------------------------------------------------------------
//destructor
//deletes memory
//----------------------------------------------------------------------------------------
template <class T>
	List<T>::~List	(void)
{
	Node *ptr, *qtr;
  	ptr = head;
  	qtr = head;
  	while (ptr != NULL)
  	{
   		qtr = ptr->next;		//sets node equal to item after ptr
    	delete ptr;				//deletes ptr
    	ptr = qtr;				//resets ptr to item originally after
  	}
  	delete ptr;						//deletes head
}

//----------------------------------------------------------------------------------------
//operator[]
//returns item in list at given index
//----------------------------------------------------------------------------------------

template <class T>
T&	List<T>::operator[]	(int x)
{
	if (x >= length() || x < 0)
	{
		// << "Error: Invalid index.\n";
		//exit(1);					//prints error if invalid index
		throw IndexError();
	}
	int count = 0;
	Node *ptr = head;
	while (count < x)
	{
		ptr = ptr->next;			//goes through list until it reaches given index
		count++;
	}
	return ptr->data;				//returns value at index
}

//----------------------------------------------------------------------------------------
// operator+
// creates a new list concatenating two existing lists
//----------------------------------------------------------------------------------------

template <class T>
List<T>	List<T>::operator+	(const List<T> &l)
{
	List<T> temp;
	Node *ptr = head;
	Node *qtr = l.head;
	while (ptr != NULL)
	{
		temp.append(ptr->data);		//appends values from first list
		ptr = ptr->next;
	}
	while (qtr != NULL)
	{
		temp.append(qtr->data);		//appends values from second list
		qtr = qtr->next;
	}
	return temp;					//returns new list
}

//----------------------------------------------------------------------------------------
//operator =
//sets two lists equal to each other
//----------------------------------------------------------------------------------------
template <class T>
List<T>	List<T>::operator= (const List<T> &src)
{
	clear();						//clears first list
	Node *ptr = src.head;
	while (ptr != NULL)
	{
		append(ptr->data);			//appends values from second list
		ptr = ptr->next;
	}
	return *this;					//returns (updated) first list
}
//----------------------------------------------------------------------------------------
//isEmpty
//returns boolean value indicating if list is empty
//----------------------------------------------------------------------------------------

template <class T>
bool	List<T>::isEmpty	(void)
{
	return (head == NULL);
}

//----------------------------------------------------------------------------------------
//length
//returns length of linked list/counts items
//----------------------------------------------------------------------------------------

template <class T>
int		List<T>::length		(void)
{
	int length = 0;
	Node *ptr = head;
	while (ptr != NULL)
	{
		ptr = ptr->next;			//increases count for every node
		length++;
	}
	return length;
}

//----------------------------------------------------------------------------------------
//toString
//converts elements in list to a string
//----------------------------------------------------------------------------------------
template <class T>
string	List<T>::toString	(void)
{
	stringstream s;
	Node *ptr = head;
	while (ptr != NULL)
	{
		s << ptr->data << " ";		//adds each value to stringstream
		ptr = ptr->next;
	}
	return s.str();
}

//----------------------------------------------------------------------------------------
//append
//adds a link with a value to the end of the list
//----------------------------------------------------------------------------------------
template <class T>
void List<T>::append (T x)
{
	Node *ptr = new Node;   		//makes next link to attach to list
  	ptr->data = x;
  	ptr->next = NULL;

  	if (head == NULL)
      	head = ptr;					//for empty list, sets head to new value
  	else
 	{
    	//case 2: insert link at the end of a non empty list
    	Node *qtr = head;
    	while (qtr->next != NULL)   //find the last link
      		qtr = qtr->next;
    	qtr->next = ptr;    		//adds the new item
  	}
}


//----------------------------------------------------------------------------------------
//insert
//inserts an item at the given position
//----------------------------------------------------------------------------------------

template <class T>
void	List<T>::insert	(T i, int p)
{
	if (p > length() || p < 0)
	{
		//cout << "Error: invalid index.\n";
		//exit(1);					//prints error message and exits program
		throw IndexError();
	}
	Node *ptr = head;
	int count = 0;
	if (p == 0)
	{
		Node *qtr = new Node;
		qtr->data = i;
		qtr->next = ptr;
		head = qtr;
	}
	else
	{
		while (count < (p-1))			//need to stop one before desired index to
		{								//make new node in the right place
			ptr = ptr->next;
			count++;					//goes through list until desired index
		}
		Node *qtr = new Node;			//sets new node equal to given item and
		qtr->data = i;					//pointing to next node
		qtr->next = ptr->next;
		ptr->next = qtr;				//creates link to new node
	}
}

//----------------------------------------------------------------------------------------
//remove
//removes item at given index
//----------------------------------------------------------------------------------------

template <class T>
void	List<T>::remove	(int p)
{
	if (p >= length() || p < 0)
	{
		//cout << "Error: invalid index.\n";
		//exit(1);					//prints error message and quits program
		throw IndexError();
	}
	Node *ptr = head;
	Node *qtr = head;
	Node *rm;
	int count = 0;
	if (p == 0)
	{
		rm = ptr;
		delete rm;
		head = ptr->next;
	}
	else
	{
		while (count < (p-1))
		{
			ptr = ptr->next;			//goes through list until index right before p
			qtr = qtr->next;
			count++;
		}
		ptr = ptr->next;
		rm = ptr;
		ptr = ptr->next;
		qtr->next = ptr;
		delete rm;

	}
}
//----------------------------------------------------------------------------------------
// clear
//deletes the links from the list
//----------------------------------------------------------------------------------------
template <class T>
void List<T>::clear (void)
{
	Node *ptr, *qtr;
  	ptr = head;
  	qtr = head;
  	while (ptr != NULL)
  	{
   		qtr = ptr->next;		//sets node equal to item after ptr
    	delete ptr;				//deletes ptr
    	ptr = qtr;				//resets ptr to item originally after
  	}
  	delete ptr;						//deletes head
	head = NULL;
}
