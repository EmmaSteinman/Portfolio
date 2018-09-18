//------------------------------------------------------------------------
//Hannah Kerr and Emma Steinman
//bst.cpp
//implements methods for bst class
//November 1, 2017
//------------------------------------------------------------------------


#include <string>
#include <sstream>
using namespace std;


//--------------------------------------------------------------
// default constructor
// creates an empty tree with root set to NULL
//--------------------------------------------------------------
template <class KeyType>
BST<KeyType>::BST (void)
{
	root = NULL;
}
//--------------------------------------------------------------
// destructor
//--------------------------------------------------------------
template<class KeyType>
BST<KeyType>::~BST (void)
{
	Node<KeyType> *ptr = root;
  if ( ptr != NULL )
	{
		clear(ptr->left);
		clear(ptr->right);
		ptr = NULL;
		delete ptr;
	}
}
//--------------------------------------------------------------
// copy constructor
// creates new bst from a preexisting bst
//--------------------------------------------------------------
template <class KeyType>
BST<KeyType>::BST (const BST<KeyType>& ptr)
{
	root = copy(ptr.root);
}
//--------------------------------------------------------------
// Empty
// tests if the bst is empty or not, returns a bool
// true (1) if the bst is empty
// false(0) if the bst is not empty
//--------------------------------------------------------------
template <class KeyType>
bool BST<KeyType>::Empty (void) const
{
	return ( root == NULL );
}

//--------------------------------------------------------------
// get
// returns a KeyType pointer to the first instance of the  parameter value
//--------------------------------------------------------------
template <class KeyType>
KeyType* BST<KeyType>::get (const KeyType& k)
{
	Node<KeyType> *ptr = root;
	if (ptr == NULL){
		cout << "Error: empty tree" << endl;
		exit(1);
	}
	while (ptr != NULL and *(ptr->data) != k)
	{
		if (k < *(ptr->data))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return ptr->data;
}
//--------------------------------------------------------------
// copy
// private function
// copies the bst from a given node
//--------------------------------------------------------------
template <class KeyType>
Node<KeyType> * BST<KeyType>::copy (Node<KeyType> *ptr)	//changed return type
{
	if(ptr == NULL)
		return NULL;
	else
	{
		Node<KeyType> *qtr = new Node<KeyType>;
		qtr->data = ptr->data;
		qtr->left = copy(ptr->left);
		qtr->right = copy(ptr->right);
		return qtr;
	}
}
//--------------------------------------------------------------
// insert
// inserts the value given as the parameter into the correct
// node in the bst.
// pre-condition: It is assumed that the bst is valid
// post-condition: The bst is valid after insertion
//--------------------------------------------------------------
template <class KeyType>
void BST<KeyType>::insert (KeyType *k)
{
	Node<KeyType> *K = new Node<KeyType>; 		//node to be inserted
	K->data = k;
	K->left = NULL;
	K->right = NULL;
	Node<KeyType> *qtr = NULL;
	Node<KeyType> *ptr = root;
	while (ptr != NULL)
	{
		qtr = ptr;
		if (*(K->data) < *(ptr->data))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	if (qtr == NULL)
	{
		root = K;
	}
	else if (*(K->data) < *(qtr->data))
	{
		qtr->left = K;
	}
	else
		qtr->right = K;
}
//--------------------------------------------------------------
// remove
// removes and deletes the node of the first instance of the
// value passed as a parameter
// pre-condition: the bst is valid
// post-condition: the bst is still valid after removal
//--------------------------------------------------------------
template <class KeyType>
void BST<KeyType>::remove (const KeyType& k)
{
	Node<KeyType> *K = find(root, k);
	Node<KeyType> *parent = findParent(root, k);
	if (K->left == NULL && K->right ==NULL) 		//case 1: no children
	{
		if (*(parent->data) < *(K->data))
			parent->right = NULL;
		else
			parent->left = NULL;
		delete K;
	}
	else if (K->left == NULL && K->right != NULL) 	//case 2: one child (right)
	{
		if (*(K->right->data) < *(parent->data))
		{
			parent->left = K->right;
			delete K;
		}
		else
		{
			parent->right = K->right;
			delete K;
		}
	}
	else if (K->left != NULL && K->right == NULL) 	//one child (left)
	{
		if (*(K->left->data) < *(parent->data))
		{
				parent->left = K->left;
				delete K;
		}
		else
		{
			parent->right = K->left;
			delete K;
		}
	}
	else 				//case 3: two children
	{
		Node<KeyType> *succ = find(root, *successor(k));
		KeyType temp = *(succ->data);
		remove(*(succ->data));
		*(K->data) = temp;
	}
}
//--------------------------------------------------------------
// findParent
// private function
// finds and returns the node that is the parent of the first instance
// of the KeyType parameter value
//--------------------------------------------------------------
template <class KeyType>
Node<KeyType> * BST<KeyType>::findParent (Node <KeyType> *ptr, KeyType item) const
{
	if (ptr->left == NULL && ptr->right == NULL)
	   return NULL;
	else if (ptr->left && *((ptr->left)->data) == item)
		  return ptr;
	else if (ptr->right && *((ptr->right)->data) == item)
	   return ptr;
	else
	{
		Node<KeyType> *qtr = NULL;
		if(ptr->left != NULL)
			qtr = findParent(ptr->left, item);
		if(qtr == NULL && ptr->right != NULL)
			qtr = findParent(ptr->right, item);
		return qtr;
	}
	return NULL;
}
//--------------------------------------------------------------
// maximum
// returns a KeyType pointer to the maximum element in the bst
//--------------------------------------------------------------
template<class KeyType>
KeyType* BST<KeyType>::maximum (void) const
{
	Node<KeyType> *ptr = root;
	if (ptr == NULL)
	{
		cout << "Error: empty tree" << endl;
		//exit(1);
	}
	while (ptr->right != NULL)
		ptr = ptr->right;
	return ptr->data;
}
//--------------------------------------------------------------
// minimum
// returns a KeyType pointer to the minimum element in the bst
//--------------------------------------------------------------
template<class KeyType>
KeyType* BST<KeyType>::minimum (void) const
{
	Node<KeyType> *ptr = root;
	if (ptr == NULL)
	{
		cout << "Error: empty tree" << endl;
		//exit(1);
	}
	while (ptr->left != NULL)
    ptr = ptr->left;
  return ptr->data;
}
//--------------------------------------------------------------
// successor
// returns a KeyType pointer to the successor of the first instance
// of the KeyType parameter value
//--------------------------------------------------------------
template<class KeyType>
KeyType* BST<KeyType>::successor  (const KeyType& k) const
{
	Node<KeyType> *K = find(root, k); 		//case 1: find smallest value in right subtree
	if (K->right != NULL)
	{
		K = K->right;
		while (K->left != NULL)
		{
			K = K->left;
		}
		return K->data;
	}
	Node<KeyType> *parent = findParent(root, k);
	while (parent != NULL && K == parent->right)
	{
		K = parent;
		parent = findParent(root, *(parent->data));
	}
	return parent->data;
}
//--------------------------------------------------------------
// predecessor
// returns a KeyType pointer to the predecessor of the first
// instance of the KeyType parameter value
//--------------------------------------------------------------
template<class KeyType>
KeyType* BST<KeyType>::predecessor  (const KeyType& k) const
{
	Node<KeyType> *K = find(root, k);
	if (K->left != NULL)
	{
		K = K->left;
		while (K->right != NULL)
		{
			K = K->right;
		}
		return K->data;
	}
	Node<KeyType> *parent = findParent(root, k);
	while (parent != NULL && K == parent->left)
	{
		K = parent;
		parent = findParent(root, *(parent->data));
	}
	return parent->data;
}
//--------------------------------------------------------------
// inHelper
// private inOrder helper function.
// recursively creates a string of KeyType values by inOrder traversal
// base case: if r is NULL, returns the string parameter with no changes
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::inHelper (Node<KeyType> *r, stringstream &s) const
{
	if (r != NULL)
	{
		inHelper(r->left, s);
		s << (*r->data);
		s << ' ';
		inHelper(r->right, s);
	}
	return s.str();
}
//--------------------------------------------------------------
// inOrder
// returns a string of KeyType values in inOrder traversal
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::inOrder (void) const
{
	stringstream s;
	if (root == NULL)
	{
		return "Empty tree";
	}
	string str = inHelper(root, s);
	str.pop_back(); 		//to get rid of the trailing space created in helper func.
	return str;
}
//--------------------------------------------------------------
// preHelper
// private preOrder helper function.
// recursively creates a string of KeyType values by preOrder traversal
// base case: if r is NULL, returns the string parameter with no changes
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::preHelper (Node<KeyType> * r, stringstream &s) const
{
	if (r != NULL)
	{
		s <<(*r->data);
		s << ' ';
		preHelper(r->left, s);
		preHelper(r->right, s);
	}
	return s.str();
}
//--------------------------------------------------------------
// preOrder
// returns a string of KeyType values in preOrder traversal
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::preOrder (void) const
{
	stringstream s;
	if (root == NULL)
	{
		return "Empty tree";
	}
	string str = preHelper(root, s);
	str.pop_back(); 		//to get rid of the trailing space created in helper func.
	return str;
}
//--------------------------------------------------------------
// postHelper
// private postOrder helper function.
// recursively creates a string of KeyType values by postOrder traversal
// base case: if r is NULL, returns the string parameter with no changes
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::postHelper (Node<KeyType> * r, stringstream &s) const
{
	if (r != NULL)
	{
		postHelper(r->left, s);
		postHelper(r->right, s);
		s << (*r->data);
		s << ' ';
	}
	return s.str();
}
//--------------------------------------------------------------
// postOrder
// returns a string of KeyType values in postOrder traversal
//--------------------------------------------------------------
template<class KeyType>
string BST<KeyType>::postOrder (void) const
{
	stringstream s;
	if (root == NULL)
	{
		return "Empty tree";
	}
	string str = postHelper(root, s);
	str.pop_back(); 		//to get rid of the trailing space created in helper func.
	return str;
}
//--------------------------------------------------------------
// assignment operator (=)
//--------------------------------------------------------------
template<class KeyType>
BST<KeyType>     BST<KeyType>::operator=   (const BST<KeyType> &ptr)
{
	clear(root);
	root = NULL;
	root = copy(ptr.root);
	return *this;
}
//--------------------------------------------------------------
// clear
// private function that clears the subtree from a given node
//--------------------------------------------------------------
template <class KeyType>
void BST<KeyType>::clear (Node<KeyType> *& ptr)
{
	if ( ptr != NULL )
	{
		clear(ptr->left);
		clear(ptr->right);
		ptr = NULL;
		delete ptr;
	}
}
//--------------------------------------------------------------
// find
// private funciton that returns the node of the first instance
// of the KeyType parameter
//--------------------------------------------------------------
template <class KeyType>
Node<KeyType> * BST<KeyType>::find (Node<KeyType> *ptr, KeyType item) const
{
	if (root == NULL){
		cout << "Error: empty tree" << endl;
		exit(1);
	}

	if(ptr == NULL)
		return NULL;

	else if(*(ptr->data) == item)
		return ptr;

	else if(*(ptr->data) != item)
	{
		Node<KeyType> *qtr = find(ptr->left, item);
		if(qtr == NULL)
			return find(ptr->right, item);
		else
			return qtr;
	}
	else
		return NULL;
}
