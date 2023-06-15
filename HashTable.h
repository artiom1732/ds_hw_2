#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "Costumer.h"

class HashTable
{
public:
    int size;
    int max_size;
    Costumer** costumers;
    HashTable(int sz=10);
    ~HashTable();
    void largerTable(Costumer** to_resize); //still O(n)?  
    void addCostumer(int id,int number);
    int getPhone(int id);
    Costumer* Find(int id);
};

#endif