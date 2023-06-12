#include "recordsCompany.h"

RecordsCompany::RecordsCompany():disks(nullptr),costumers(nullptr),vip_costumers(nullptr){}

RecordsCompany::~RecordsCompany(){delete disks;delete costumers;delete vip_costumers;}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    //free old data
    disks = new UnionFind(records_stocks,number_of_records);
    costumers = new HashTable();
    vip_costumers = new AVLTree<VipCostumer>();
    return SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    costumers->addCostumer(c_id,phone);
    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    return costumers->getPhone(c_id);
}

StatusType RecordsCompany::makeMember(int c_id)
{
    vip_costumers->treeInsert(c_id,new VipCostumer(c_id));
    return SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(vip_costumers->Find(c_id))
    {
        return true;
    }
    return false;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    //to be done
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    //to be done
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    //to be done
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    disks->Union(r_id1,r_id2);
    return SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    disks->getPlace(r_id,column,hight);
    return SUCCESS;
}


