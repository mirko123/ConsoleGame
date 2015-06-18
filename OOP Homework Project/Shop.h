#ifndef __OOP_Homework_Project__Shop__
#define __OOP_Homework_Project__Shop__

#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Creature.h"
using namespace std;

class Shop
{
private:
    map<string, int> price;
public:
    Shop();
    map<string, int> Units();
    bool Buy(Creature* type, vector< pair<Creature*, int> > &playerUnits, int &playerGold, int count = 1 );
};

#endif /* defined(__OOP_Homework_Project__Shop__) */
