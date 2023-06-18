#include "recordsCompany.h"
#include <exception>

RecordsCompany::RecordsCompany():Disks(nullptr),Costumers(new HashTable()),Vip_Costumers(new AVLTree<Costumer>()){}

RecordsCompany::~RecordsCompany(){delete Disks;delete Costumers;delete Vip_Costumers;}


static void clearVipCostumers(TreeNode<Costumer>* root)
{
    if(root == nullptr)
    {
        return;
    }
    clearVipCostumers(root->left);
    root->data->extra = 0;
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
        try
        {
            Disks = new UnionFind(records_stocks,number_of_records);
        }
        catch(const std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }
    delete Disks;
    try
    {
        Disks = new UnionFind(records_stocks,number_of_records);
    }
    catch(const std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
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
    try
    {
        Costumers->addCostumer(c_id,phone);

    }
    catch(const std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
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
    TreeNode<Costumer>* temp = Vip_Costumers->Find(c_id);
    if(temp != nullptr)
    {
        return ALREADY_EXISTS;
    }
    Costumer* cur = Costumers->Find(c_id);
    try
    {
        Vip_Costumers->treeInsert(c_id,new Costumer(cur->id,cur->phone_number));
        cur->vip = true;
    }
    catch(const std::exception& e)
    {
        return ALLOCATION_ERROR;
    }
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
    return temp->vip;
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
    TreeNode<Costumer>* temp = Vip_Costumers->Find(c_id);
    if(temp)
    {
        temp->data->expenses = temp->data->expenses + 100 + Disks->elements[r_id]->sells++;
        return SUCCESS;
    }
    Disks->elements[r_id]->sells++;
    return SUCCESS;
}


void Add(TreeNode<Costumer>* root,int index,int orig_index,int amount)
{
    bool went_right = false;
    bool already_added = false;
    while(root != nullptr)
    {
        if(root->key < index && !went_right)
        {
            already_added = true;
            went_right = true;
            root->data->extra += amount;
            root = root->right;
            continue;
        }
        if(root->key < index && went_right)
        {
            went_right = true;
            root = root->right;
            continue;
        }
        if(root->key > index && went_right)
        {
            went_right = false;
            root->data->extra -= amount;
            root = root->left;
            continue;
        }
        if(root->key > index && !went_right)
        {
            went_right = false;
            root = root->left;
            continue;
        }
        if(orig_index <= index)
        {
            if(root->key == index && went_right)  
            {
                if(already_added)
                {
                    root->data->extra -= amount;
                }
                if(root->left != nullptr)
                {
                    root->left->data->extra += amount;
                }
                return;
            }
            else if(root->key == index && !went_right)
            {
                if(root->left != nullptr)
                {
                    root->left->data->extra += amount;
                }
                return;
            }
        }
        else if(orig_index > index)
        {
            if(root->key == index && went_right)  
            {
                if(root->right != nullptr)
                {
                    root->right->data->extra -= amount;
                }
                return;
            }
            else if(root->key == index && !went_right)
            {
                root->data->extra += amount;
                if(root->right != nullptr)
                {
                    root->right->data->extra += amount;
                }
                return;
            }
        }
    }
}

int getClosest(TreeNode<Costumer>* root,int target)
{
    int cur_closest = root->key;
    while(root != nullptr)
    {
        if(root->key == target)
        {
            return root->key;
        }
        if(root->key < target)
        {
            cur_closest = root->key;
            root = root->right;
            continue;
        }
        if(root->key > target)
        {
            cur_closest = root->key;
            root = root->left;
            continue;
        }
    }
    return cur_closest;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1 < 0 || (c_id2 < c_id1) || amount <= 0)
    {
        return INVALID_INPUT;
    }
    if(Vip_Costumers->head == nullptr)
    {
        return SUCCESS;
    }
    Add(Vip_Costumers->head,getClosest(Vip_Costumers->head,c_id2),c_id2,amount);
    Add(Vip_Costumers->head,getClosest(Vip_Costumers->head,c_id1),c_id1,-amount);
    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id < 0)
    {
        return INVALID_INPUT;
    }
    TreeNode<Costumer>* temp = Vip_Costumers->Find(c_id);
    if(temp == nullptr)
    {
        return DOESNT_EXISTS;
    }
    return temp->data->expenses - temp->calcPrize(Vip_Costumers->head,c_id);
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


