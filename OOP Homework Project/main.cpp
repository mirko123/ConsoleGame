#include <iostream>
#include "Creature.h"
#include "Player.h"
#include "Shop.h"
#include "Game.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    
    Game* game = new Game();
    game->BaseMenu("go in shop");
    game->BaseMenu("start game");

    
    return 0;
}
