#include "HashTable.h"

int HashFunc(int n,int m)
{
    return n%m;
}

HashTable::HashTable(int sz):size(0),max_size(sz),costumers(new AVLTree<Costumer>*[sz])
{
    for(int i=0;i<sz;i++)
    {
        costumers[i] = new AVLTree<Costumer>();
    }
}


HashTable::~HashTable()
{
    for(int i=0;i<max_size;i++)
    {
        if(costumers[i] != nullptr)
        {
            delete costumers[i];
        }
    }
    delete[] costumers;
}

void CopyTrees(TreeNode<Costumer>* root,AVLTree<Costumer>** data,int size)
{
    if(root == nullptr)
    {
        return;
    }
    CopyTrees(root->left,data,size);
    data[HashFunc(root->data->id,size)]->treeInsert(root->key,new Costumer(root->data->id,root->data->phone_number));
    CopyTrees(root->right,data,size);
}

void HashTable::largerTable(AVLTree<Costumer>** to_resize) //still O(n)?  
{
    max_size = max_size * 2;
    AVLTree<Costumer>** temp = costumers;
    costumers = new AVLTree<Costumer>*[max_size];
    for(int i=0;i<max_size;i++)
    {
        costumers[i] = new AVLTree<Costumer>();
    }
    size = 0;
    for(int i=0;i<max_size/2;i++)
    {
        TreeNode<Costumer>* cur_head = temp[i]->head;
        CopyTrees(cur_head,costumers,max_size);
        delete temp[i];
    }
    delete[] temp;
}



void HashTable::addCostumer(int id,int number)
{
    int index = HashFunc(id,max_size);
    costumers[index]->treeInsert(id,new Costumer(id,number));
    size++;
    if(size > max_size/2)
    {
        largerTable(costumers);
    }
}

Costumer* HashTable::Find(int id)
{
    int index = HashFunc(id,max_size);
    TreeNode<Costumer>* temp = costumers[index]->Find(id);
    if(temp == nullptr)
    {
        return nullptr;
    }
    return temp->data;
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