#ifndef _COSTUMER
#define _COSTUMER


class Costumer
{
public:
    int id;
    int phone_number;
    bool vip;
    double extra;
    double expenses;
    Costumer(int id,int number,bool member = false):id(id),phone_number(number),vip(member),extra(0),expenses(0){}
};

#endif