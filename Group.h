#ifndef _GROUP
#define _GROUP

#include "Disk_Node.h"

class Group
{
public:
    int group_id;
    int size;
    Disk_Node* base_of_column;
    int height;
    Disk_Node* head;
    Group(Disk_Node* head,int id):group_id(id),size(1),base_of_column(head),height(head->cd_amount),head(head){}
};

#endif