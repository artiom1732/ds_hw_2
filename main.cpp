#include <iostream>
#include "recordsCompany.h"

int main(int,char**)
{
    HashTable* tab  = new HashTable();
    tab->addCostumer(4,11);
    tab->addCostumer(2,12);
    tab->addCostumer(6,13);
    tab->addCostumer(12,14);
    std::cout<<tab->getPhone(1)<<std::endl;
    return 0;
}