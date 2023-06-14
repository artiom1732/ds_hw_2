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
        temp->r = sumR;
        to_subtract = to_subtract + temp->r;
        sumR = sumR - temp->r;
        Disk_Node* next = temp->up;
        temp->up = root;
        temp = next;
    }
    return root->group;
}

Group* UnionFind::Union(int b,int a)
{
    if(Connected(a,b))
    {
        return nullptr;
    }
    Group* A = Find(a);   //g_1 = A
    Group* B = Find(b);   //g_2 = B
    if(A->size < B->size)
    {
        A->head->up = B->head;
        B->size += A->size;
        B->group_id = ++group_counter;
        B->height += A->height;
        B->head->r += A->height;
        A->head->r = A->head->r - B->head->r;
        A->head->group = nullptr;
        return B;
    }
    B->head->up = A->head;
    A->size += B->size;
    A->group_id = ++group_counter;
    B->head->r = B->head->r + A->height - A->head->r;
    B->head->group = nullptr;
    return A;
}

bool UnionFind::Connected(int a,int b)
{
    return Find(a) == Find(b);
}

void UnionFind::getPlace(int r_id,int* column,int* height)
{
    Group* temp = Find(r_id);
    *column = temp->column;
    *height = 0;
    Disk_Node* root = elements[r_id];
    while(root!=nullptr)
    {
        *height += root->r;
        root = root->up;
    }
}