//Emma Steinman & Lindsey Siegfried
//dictionary.h
//This file implements a dictionary via inheritance from our bst class
//November 10, 2017

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "HashTable.h"

template <class KeyType>
class Dictionary: public HashTable<KeyType>
{

public:
              Dictionary  (){};    //default constructor
              ~Dictionary (void){};    //destructor
              Dictionary  (const Dictionary<KeyType> &d){};     //copy constructor
  void        insert      (KeyType *k)
  {
    HashTable<KeyType>::insert(k);
  };
  void        remove      (const KeyType &k)
  {
    HashTable<KeyType>::remove(k);
  };
  KeyType *   get         (const KeyType &k) const
  {
    HashTable<KeyType>::get(k);
  };
  bool        Empty       (void)  const
  {
    HashTable<KeyType>::Empty();
  };

private:
  HashTable<KeyType> *d;

};
#endif
