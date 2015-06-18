#include "Player.h"
using namespace std;

Player::Player(string PlayerName)
{
    this->name = PlayerName;
    pair<Creature*, int> pair(new Hero(), 1);
    playerUnits.push_back(pair);
}
void Player::SetName(string name)
{
    this->name = name;
}
string Player::GetName()
{
    return this->name;
}
int Player::GetGold()
{
    return this->gold;
}
void Player::AddGold(int value)
{
    this->gold+=value;
}
bool Player::Buy(Shop* &shop, Creature* type, int count)
{
    return shop->Buy(type, this->playerUnits, this->gold, count);
}
void Player::SetPlayerUnits(vector< pair<Creature*, int> > playerUnits)
{
    this->playerUnits = playerUnits;
}
vector< pair<Creature*, int> > Player::GetUnits()
{
    return this->playerUnits;
}