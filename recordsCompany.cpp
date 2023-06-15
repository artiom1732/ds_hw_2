#include "recordsCompany.h"

RecordsCompany::RecordsCompany():Disks(nullptr),Costumers(new HashTable()),Vip_Costumers(new AVLTree<VipCostumer>()){}

RecordsCompany::~RecordsCompany(){delete Disks;delete Costumers;delete Vip_Costumers;}


static void clearVipCostumers(TreeNode<VipCostumer>* root)
{
    if(root == nullptr)
    {
        return;
    }
    clearVipCostumers(root->left);
    root->data->prize = 0;
    root->data->expenses = 0;
    clearVipCostumers(root->right);
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
    {
        return INVALID_INPUT;
    }
    if(!Disks)
    {
        Disks = new UnionFind(records_stocks,number_of_records);
        return SUCCESS;
    }
    delete Disks;
    Disks = new UnionFind(records_stocks,number_of_records);
    clearVipCostumers(Vip_Costumers->head);
    return SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
    {
        return INVALID_INPUT;
    }
    if(Costumers->Find(c_id) != nullptr)
    {
        return ALREADY_EXISTS;
    }
    Costumers->addCostumer(c_id,phone);
    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    int result = Costumers->getPhone(c_id);
    if(result < 0)
    {
        return DOESNT_EXISTS;
    }
    return result;
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    if(Costumers->Find(c_id) == nullptr)
    {
        return DOESNT_EXISTS;
    }
    TreeNode<VipCostumer>* temp = Vip_Costumers->Find(c_id);
    if(temp != nullptr)
    {
        return ALREADY_EXISTS;
    }
    Vip_Costumers->treeInsert(c_id,new VipCostumer(c_id));
    return SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    Costumer* temp = Costumers->Find(c_id);
    if(temp == nullptr)
    {
        return DOESNT_EXISTS;
    }
    if(Vip_Costumers->Find(c_id) == nullptr)
    {
        return false;
    }
    return true;
}


StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
    {
        return INVALID_INPUT;
    }
    if(r_id >= Disks->number_of_records || Costumers->Find(c_id) == nullptr)
    {
        return DOESNT_EXISTS;
    }
    TreeNode<VipCostumer>* temp = Vip_Costumers->Find(c_id);
    if(temp)
    {
        temp->data->expenses = temp->data->expenses + 100 + Disks->elements[r_id]->sells++;
        return SUCCESS;
    }
    Disks->elements[r_id]->sells++;
    return SUCCESS;
}

void AddPrizeInOrder(TreeNode<VipCostumer>* head,int c_id1,int c_id2,double amount)
{
    if(head == nullptr)
    {
        return;
    }
    AddPrizeInOrder(head->left,c_id1,c_id2,amount);
    if(head->data->id >= c_id1 && head->data->id < c_id2)
    {
        head->data->prize += amount;
    }
    AddPrizeInOrder(head->right,c_id1,c_id2,amount);
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1 < 0 || (c_id2 < c_id1) || amount <= 0)
    {
        return INVALID_INPUT;
    }
    AddPrizeInOrder(Vip_Costumers->head,c_id1,c_id2,amount);
    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    TreeNode<VipCostumer>* temp = Vip_Costumers->Find(c_id);
    if(temp == nullptr)
    {
        return DOESNT_EXISTS;
    }
    return temp->data->expenses - temp->data->prize;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1 < 0 || r_id2 < 0)
    {
        return INVALID_INPUT;
    }
    if(r_id1 >= Disks->number_of_records || r_id2 >= Disks->number_of_records)
    {
        return DOESNT_EXISTS;
    }
    if(Disks->Union(r_id1,r_id2) == nullptr)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id < 0 || !column || ! hight)
    {
        return INVALID_INPUT;
    }
    if(r_id >= Disks->number_of_records)
    {
        return DOESNT_EXISTS;
    }
    Disks->getPlace(r_id,column,hight);
    return SUCCESS;
}


