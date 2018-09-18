//=========================================================
// Emma Steinman
// Stack.h
// April 7, 2017
// This file is a templated Stack class
//=========================================================

#ifndef STACK_H
#define STACK_H

#include "List.h"

template <class T>
class Stack
{
private:
	List<T>	list;



public:
	void		push		(T);
	T				pop			(void);
	T	 			peek		(void);
	int			length		(void) const;
	bool		isEmpty		(void) const;
	void		clear		(void);

					Stack		(void);
					~Stack		(void);
					Stack		(const Stack<T> &);
	Stack<T>	operator=	(const Stack<T> &);

	friend ostream & operator<< (ostream &os, const Stack<T> &s)
	{
		os << s.list;
		return os;
	}

};




//=========================================================
template <class T>
		Stack<T>::Stack		(void)
{
	//secretly creates private variables, no code needed
}
//=========================================================
template <class T>
		Stack<T>::~Stack		(void)
{
	//secretly deletes
}
//=========================================================
template <class T>
		Stack<T>::Stack		(const Stack<T> &s)
{
	list = s.list;
}
//=========================================================
template <class T>
Stack<T>	Stack<T>::operator=		(const Stack<T> &s)
{
						//constructor
						//destructor
	list = s.list;		//copy constructor
	return *this;
}
//=========================================================
template <class T>
void		Stack<T>::push		(T item)
{
	list.insert(item, 0);
}
//=========================================================
template <class T>
T		Stack<T>::pop		(void)
{
	T temp = list[0];
	list.remove(0);
	return temp;
}
//=========================================================
template <class T>
T		Stack<T>::peek		(void)
{
	return list[0];
}
//=========================================================
template <class T>
int		Stack<T>::length	(void) const
{
	return list.length();
}
//=========================================================
template <class T>
bool	Stack<T>::isEmpty	(void) const
{
	return (list.length()==0);
}
//=========================================================
template <class T>
void	Stack<T>::clear		(void)
{
	list.clear();
}
#endif
