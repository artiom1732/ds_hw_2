#ifndef _UNION_FIND
#define _UNION_FIND

#include "Disk_Node.h"
#include "Group.h"

class UnionFind
{
public:
    int group_counter;
    Disk_Node** elements;
    Group** groups;
    int number_of_records;
    int sells;
    UnionFind(int* input,int input_size);
    ~UnionFind(){delete[] elements;delete[] groups;}
    Group* Find(int a);
    Group* Union(int b,int a);   // putting b on a
    bool Connected(int a,int b);
    void getPlace(int r_id,int* column,int* height);
};

#endif