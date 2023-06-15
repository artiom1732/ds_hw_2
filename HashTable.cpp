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


HashTable::~HashTable()
{
    for(int i=0;i<max_size;i++)
    {
        Costumer* temp = costumers[i];
        while(temp)
        {
            Costumer* next = temp->next;
            delete temp;
            temp = next;
        }
    }
    delete[] costumers;
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
            delete cur;
            cur = next;
        }
    }
    delete[] temp;
}

void HashTable::addCostumer(int id,int number)
{
    int index = HashFunc(id,max_size);
    if(costumers[index] == nullptr)
    {
        costumers[index] = new Costumer(id,number);
        size++;
        if(size > max_size/2)
        {
            largerTable(costumers);
        }
        return;
    }
    Costumer* temp = costumers[index];
    while(temp->next != nullptr)
    {
        if(temp->id == id)
        {
            return;
        }
        temp = temp->next;
    }
    if(temp->id == id)
    {
        return;
    }
    temp->next = new Costumer(id,number);
    size++;
    if(size > max_size/2)
    {
        largerTable(costumers);
    }
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
    return -1;
}