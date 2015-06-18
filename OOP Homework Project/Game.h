#ifndef __OOP_Homework_Project__Game__
#define __OOP_Homework_Project__Game__

#include <iostream>
#include "Creature.h"
#include "Player.h"
#include "Shop.h"
#include "Game.h"
#include "Battlefield.h"
#include <string>
#include <vector>
#include <map>

class Game
{
private:
    Player* m_player;
    Player* m_enemy;
    void PrintUnitsPrice(Shop* &shop);
    void ShopingUnits(Player* &player, Shop* &shop);
    void AutoAttack(Player* &player, Battlefield* &field);
public:
    Game();
    void BaseMenu(string command);
    void ShopMenu();
    void GameMenu();
};

#endif /* defined(__OOP_Homework_Project__Game__) */
