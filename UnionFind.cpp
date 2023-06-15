#include "UnionFind.h"

UnionFind::UnionFind(int* input,int input_size):group_counter(0),elements(new Disk_Node*[input_size]),groups(new Group*[input_size]),number_of_records(input_size)
{
    for(int i=0;i<input_size;i++)
    {
        elements[i] = new Disk_Node(i,input[i]);
        groups[i] = new Group(elements[i],i);
        elements[i]->AddGroup(groups[i]);
        group_counter++;
    }
}

UnionFind::~UnionFind()
{
    for(int i=0;i<number_of_records;i++)
    {
        delete elements[i];
        delete groups[i];
    }
    delete[] groups;
    delete[] elements;
}

Group* UnionFind::Find(int a)
{
    int sumR = 0;
    Disk_Node* root = elements[a];
    while(root->up!=nullptr)
    {
        sumR += root->r;
        root = root->up;
    }
    //path compression
    Disk_Node* temp = elements[a];
    int to_subtract = 0;
    while(temp!=root)
    {
        int temp_r = temp->r;
        temp->r = sumR - to_subtract;
        Disk_Node* next = temp->up;
        temp->up = root;
        temp = next;
        to_subtract = to_subtract + temp_r;
    }
    return root->group;
}

Group* UnionFind::Union(int b,int a)    //b is put on a
{
    if(Connected(a,b))
    {
        return nullptr;
    }
    Group* A = Find(a);  
    Group* B = Find(b);  
    if(A->size < B->size)
    {
        A->head->up = B->head;
        B->size += A->size;
        B->group_id = ++group_counter;
        B->head->r += A->height;
        A->head->r = A->head->r - B->head->r;
        A->head->group = nullptr;
        B->height += A->height;
        B->base_of_column = A->base_of_column;
        return B;
    }
    B->head->up = A->head;
    A->size += B->size;
    A->group_id = ++group_counter;
    B->head->r = B->head->r + A->height - A->head->r;
    B->head->group = nullptr;
    A->height += B->height;
    B->base_of_column = A->base_of_column;
    return A;
}

bool UnionFind::Connected(int a,int b)
{
    return Find(a) == Find(b);
}

void UnionFind::getPlace(int r_id,int* column,int* height)
{
    Group* temp = Find(r_id);
    *column = temp->base_of_column->id;
    *height = 0;
    Disk_Node* root = elements[r_id];
    while(root!=nullptr)
    {
        *height += root->r;
        root = root->up;
    }
}