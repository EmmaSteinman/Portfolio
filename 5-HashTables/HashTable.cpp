/*
* hash table class methods
* lindsey siegfried & emma steinman
* 10 november 2017
*/

//=============================================================
//=============================================================
//=============================================================

/*-------------------------------
* default constructor (unspecified slots)
-------------------------------*/
template <class KeyType>
    HashTable<KeyType>::HashTable(void)
{
  slots = 10;
  table = new List<KeyType>[slots];
}

/*-------------------------------
* default constructor (specified slots)
-------------------------------*/
template <class KeyType>
    HashTable<KeyType>::HashTable(int numSlots)
{
    slots = numSlots;
    table = new List<KeyType>[slots];
}

/*-------------------------------
* copy constructor
-------------------------------*/
template <class KeyType>
    HashTable<KeyType>::HashTable(const HashTable<KeyType>& h)
{
    slots = h.slots;
    table = new List<KeyType>[slots];
    for (int i = 0; i < h.slots; i++)
    {
        table[i] = h.table[i];
    }
}

/*-------------------------------
* destructor
-------------------------------*/
template <class KeyType>
    HashTable<KeyType>::~HashTable()
{
    delete[] table;
}

/*-------------------------------
* get
* this method returns a pointer to the object in the hash table where the value resides
* parameters: const KeyType& k for which to find
* return value: KeyType* location
-------------------------------*/
template <class KeyType>
KeyType* HashTable<KeyType>::get(const KeyType& k) const
{
  int index = k.hash(slots);
  return table[index].get(k);
}

/*-------------------------------
* insert
* this method inserts a value into the hash table
* parameters: KeyType* k to insert
* return value: void
-------------------------------*/
template <class KeyType>
void HashTable<KeyType>::insert(KeyType* k)
{
  int slot = k->hash(slots);
  table[slot].insert(0,k);
}

/*-------------------------------
* remove
* this method removes a given value from the hash table
* parameters: const KeyType& k to remove
* return value: void
-------------------------------*/
template <class KeyType>
void HashTable<KeyType>::remove(const KeyType& k)
{
  int slot = k.hash(slots);
  table[slot].remove(k);
}

/*-------------------------------
* assignment operator
* this operator assigns a hash table to *this
* parameters: const HashTable<KeyType>& h existing hash table to copy
* return value: HashTable<KeyType>& new hash table
-------------------------------*/
template <class KeyType>
HashTable<KeyType>& HashTable<KeyType>::operator=(const HashTable<KeyType>& h)
{
  delete[] table;
  table = h.table;
  return *this;
}

/*-------------------------------
* toString
* this method returns the list located in a given slot as a string
* parameters: int slot
* return value: string
-------------------------------*/
template <class KeyType>
string HashTable<KeyType>::toString(int slot) const
{
  List<KeyType> t = table[slot];
  return t.toString();
}


/*-------------------------------
* Empty
* this method returns whether or not the HT is empty
* parameters: void
* return value: bool
-------------------------------*/
template <class KeyType>
bool  HashTable<KeyType>::Empty(void) const
{
  return (table == NULL);
}
