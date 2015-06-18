#include "Shop.h"
using namespace std;

Shop::Shop()
{
    price["Peasant"] = 30;
    price["Footman"] = 90;
    price["Archer"] = 50;
    price["Griffon"] = 150;
}
map<string, int> Shop::Units()
{
    return price;
}
bool Shop::Buy(Creature* type, vector< pair<Creature*, int> > &playerUnits, int &playerGold, int count)
{
    if(count > 0)
    {
        if (playerGold >= price[type->GetType()]*count)
        {
            playerGold -= price[type->GetType()]*count;
            
            for (int i = 0; i < playerUnits.size(); i++)
            {
                if(playerUnits[i].first->GetType() == type->GetType())
                {
                    playerUnits[i].second += count;
                    return 1;
                    break;
                }
            }
            pair<Creature*, int> unit(type, count);
            playerUnits.push_back(unit);
            return 1;
        }
        else
        {
            cout<<"you need "<<price[type->GetType()]*count - playerGold << " gold." << endl;
            return 0;
        }
    }
    return 0;
}
