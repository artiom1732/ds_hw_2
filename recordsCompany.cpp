#include "recordsCompany.h"

RecordsCompany::RecordsCompany():disks(nullptr),costumers(nullptr),vip_costumers(nullptr){}

RecordsCompany::~RecordsCompany(){delete disks;delete costumers;delete vip_costumers;}


static void clearVipCostumers(TreeNode<VipCostumer>* root)
{
    if(root == nullptr)
    {
        return;
    }
    clearVipCostumers(root->left);
    root->data->prize -= root->data->expenses;
    root->data->expenses = 0;
    clearVipCostumers(root->right);
    root->data->prize -= root->data->expenses;
    root->data->expenses = 0;
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
    {
        return INVALID_INPUT;
    }
    if(!disks && !costumers && !vip_costumers)
    {
        disks = new UnionFind(records_stocks,number_of_records);
        costumers = new HashTable();
        vip_costumers = new AVLTree<VipCostumer>();
        return SUCCESS;
    }
    delete[] disks; //remove all old disks
    disks = new UnionFind(records_stocks,number_of_records);
    clearVipCostumers(vip_costumers->head);
    return SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id < 0 || phone < 0)
    {
        return INVALID_INPUT;
    }
    
    if(costumers->Find(c_id))
    {
        return ALREADY_EXISTS;
    }
    costumers->addCostumer(c_id,phone);
    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    int result = costumers->getPhone(c_id);
    if(result)
    {
        return result;
    }
    return DOESNT_EXISTS;
}

StatusType RecordsCompany::makeMember(int c_id)     //O(n) because hashtable
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    if(costumers->Find(c_id) == nullptr)
    {
        return DOESNT_EXISTS;
    }
    TreeNode<VipCostumer>* temp = vip_costumers->Find(c_id);
    if(temp != nullptr)
    {
        if(temp->data->id == c_id)
        {
            return ALREADY_EXISTS;
        }
    }
    vip_costumers->treeInsert(c_id,new VipCostumer(c_id));
    return SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    if(costumers->Find(c_id) == nullptr)
    {
        return DOESNT_EXISTS;
    }
    else if(vip_costumers->Find(c_id) == nullptr)
    {
        return false;
    }
    return true;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)    //O(n) because hashtable
{
    if(c_id < 0 || r_id < 0)
    {
        return INVALID_INPUT;
    }
    if(r_id >= disks->number_of_records || costumers->Find(c_id) == nullptr)
    {
        return DOESNT_EXISTS;
    }
    disks->elements[r_id]->sells++;
    TreeNode<VipCostumer>* temp = vip_costumers->Find(c_id);
    if(temp)
    {
        temp->data->expenses = temp->data->expenses + 100 + disks->elements[r_id]->sells;
        return SUCCESS;
    }
    return SUCCESS;
}

static void AddPrizeInOrder(TreeNode<VipCostumer>* root,int amount,int c_id1,int c_id2)
{
    if(root == nullptr)
    {
        return;
    }
    AddPrizeInOrder(root->left,amount,c_id1,c_id2);
    if(root->data->id <= c_id2 && root->data->id >= c_id1)
    {
        root->data->prize += amount;    
    }
    AddPrizeInOrder(root->right,amount,c_id1,c_id2);
    if(root->data->id <= c_id2 && root->data->id >= c_id1)
    {
        root->data->prize += amount;    
    }
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1 < 0 || (c_id2 < c_id1) || amount <= 0)
    {
        return INVALID_INPUT;
    }
    TreeNode<VipCostumer>* root = vip_costumers->head;
    AddPrizeInOrder(root,amount,c_id1,c_id2);
    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    TreeNode<VipCostumer>* temp = vip_costumers->Find(c_id);
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
    if(r_id1 > disks->number_of_records || r_id2 > disks->number_of_records)
    {
        return DOESNT_EXISTS;
    }
    if(disks->Union(r_id1,r_id2) == nullptr)
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
    if(r_id> disks->number_of_records)
    {
        return DOESNT_EXISTS;
    }
    disks->getPlace(r_id,column,hight);
    return SUCCESS;
}


