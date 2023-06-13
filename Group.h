#ifndef _GROUP
#define _GROUP

#include "Disk_Node.h"

class Group
{
public:
    int group_id;
    int size;
    int column;
    int height;
    Disk_Node* head;
    Group(Disk_Node* head,int id):group_id(id),size(1),column(id),height(head->cd_amount),head(head){}
};

#endif