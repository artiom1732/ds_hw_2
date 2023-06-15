#ifndef _COSTUMER
#define _COSTUMER


class Costumer
{
public:
    int id;
    int phone_number;
    Costumer* next;
    bool vip;
    Costumer(int id,int number):id(id),phone_number(number),next(nullptr),vip(false){}
};

#endif