//============================================================
// Emma Steinman
// March 24, 2017
// List.h
// Class definition for the List class dealing with Lists
//============================================================

#include <iostream>
#include <string>
using namespace std;

#ifndef LIST_H
#define LIST_H


//============================================================
// List Class
//============================================================
template <class T>
class List
{
private:
	T	 	*array;
	int		DEFAULT_LIST_SIZE = 10;
	int		capacity;
	int 	size;
	
public:
	
			List		(void);		//default
			List		(const List<T> &c);	//copy constructor
	bool	isEmpty		(void);
	int		length		(void) const;
	T&		operator[]	(int i);	//index operator
	friend ostream& operator<< (ostream &os, List<T> c)
	{
		for (int i = 0; i < c.size; i++)
			os << c[i] << " ";

		return os;
	}
	string	toString	(void)const ;
	void	append		(T c);
	void	insert		(T, int);
	void	remove		(int);
	List<T>	operator+	(const List<T> c) const ;
	List<T>	operator=	(List<T> c) const ;
	void	clear		(void);
			~List		(void);		//destructor

};

#include "List.cc"
#endif
