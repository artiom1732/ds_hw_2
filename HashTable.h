#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "Costumer.h"
#include "AvlTree.h"

class HashTable
{
public:
    int size;
    int max_size;
    AVLTree<Costumer>** costumers;
    HashTable(int sz=2);
    ~HashTable();
    void largerTable(AVLTree<Costumer>** to_resize); //still O(n)?  
    void addCostumer(int id,int number);
    int getPhone(int id);
    Costumer* Find(int id);
};

#endif