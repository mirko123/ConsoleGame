#ifndef __OOP_Homework_Project__Player__
#define __OOP_Homework_Project__Player__

#include <iostream>
#include <string>
#include "Creature.h"
#include "Shop.h"
#include <vector>
#include <map>
using namespace std;

class Player
{
private:
    vector< pair<Creature*, int> > playerUnits;
    int gold = 300;
    string name;
public:
    Player(string playerName = "PlayerName");
    void SetName(string name);
    string GetName();
    int GetGold();
    void AddGold(int value);
    bool Buy(Shop* &shop, Creature* type, int count);
    void SetPlayerUnits(vector< pair<Creature*, int> > playerUnits);
    vector< pair<Creature*, int> > GetUnits();
};

#endif /* defined(__OOP_Homework_Project__Player__) */
