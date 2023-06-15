#ifndef _DISK_NODE
#define _DISK_NODE

class Group;

class Disk_Node
{
public:
    int id; 
    int cd_amount;  //the number of cds of that type
    Disk_Node* up;   //the node above in the tree
    Group* group;
    int r;
    int sells;
    Disk_Node(int id,int amount):id(id),cd_amount(amount),up(nullptr),group(nullptr),r(0),sells(0){}
    void AddGroup(Group* to_add){group = to_add;}
};

#endif