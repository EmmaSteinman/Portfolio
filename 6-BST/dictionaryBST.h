//Hannah Kerr and Emma Steinman
//dictionary.h
//This file implements a dictionary via inheritance from our bst class
//November 1, 2017

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "bst.h"

template <class KeyType>
class Dictionary : public BST<KeyType>
{

public:
              Dictionary  (void){};    //default constructor
              ~Dictionary (void){};    //destructor
              Dictionary  (const Dictionary<KeyType> &d){};     //copy constructor


  using       BST<KeyType>::copy;               //uses copy, insert, remove, get, and Empty
  using       BST<KeyType>::insert;            //from BST class
  using       BST<KeyType>::remove;
  using       BST<KeyType>::get;
  using       BST<KeyType>::Empty;

};
#endif
