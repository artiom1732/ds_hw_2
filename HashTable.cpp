#include "HashTable.h"

int HashFunc(int n,int m)
{
    return n%m;
}

HashTable::HashTable(int sz):size(0),max_size(sz),costumers(new Costumer*[sz])
{
    for(int i=0;i<sz;i++)
    {
        costumers[i] = nullptr;
    }
}

void HashTable::largerTable(Costumer** to_resize) //still O(n)?  
{
    max_size = max_size * 2;
    Costumer** temp = costumers;
    costumers = new Costumer*[max_size];
    size = 0;
    for(int i=0;i<max_size;i++)
    {
        costumers[i] = nullptr;
    }
    for(int i=0;i<max_size/2;i++)
    {
        Costumer* cur = temp[i];
        while(cur != nullptr)
        {
            addCostumer(cur->id,cur->phone_number);
            Costumer* next = cur->next;
            delete temp[i];
            cur = next;
        }
        temp[i] = nullptr;
    }
    delete[] temp;
}

bool HashTable::addCostumer(int id,int number)
{
    int index = HashFunc(id,max_size);
    if(costumers[index] == nullptr)
    {
        if(costumers[index]->id == id)
        {
            return false;
        }
        costumers[index] = new Costumer(id,number);
        size++;
        if(size > max_size/2)
        {
            largerTable(costumers);
        }
        return true;
    }
    Costumer* temp = costumers[index];
    while(temp->next != nullptr)
    {
        if(temp->id == id)
        {
            return false;
        }
        temp = temp->next;
    }
    if(temp->id == id)
    {
        return false;
    }
    temp->next = new Costumer(id,number);
    size++;
    if(size > max_size/2)
    {
        largerTable(costumers);
    }
    return true;
}

Costumer* HashTable::Find(int id)
{
    int index = HashFunc(id,max_size);
    Costumer* temp = costumers[index];
    while(temp != nullptr)
    {
        if(temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

int HashTable::getPhone(int id)
{
    Costumer* temp = Find(id);
    if(temp != nullptr)
    {
        return temp->phone_number;
    }
    return 0;
}