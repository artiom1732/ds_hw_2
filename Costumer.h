#ifndef _COSTUMER
#define _COSTUMER


class Costumer
{
public:
    int id;
    int phone_number;
    Costumer* next;
    Costumer(int id,int number):id(id),phone_number(number),next(nullptr){}
};

#endif