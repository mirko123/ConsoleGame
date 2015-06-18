//
//  Battlefield.h
//  OOP Homework Project
//
//  Created by Мирослав Николов on 25.05.15.
//  Copyright (c) 2015 г. Мирослав Николов. All rights reserved.
//

#ifndef __OOP_Homework_Project__Battlefield__
#define __OOP_Homework_Project__Battlefield__

#include <iostream>
#include "Creature.h"
#include "Player.h"
#include "Shop.h"
//#include "Game.h"
#include "peir.h"
#include "Player.h"
#include <string>
#include <vector>
#include <map>

class Battlefield
{
private:
    Player* player1;
    Player* player2;
    Creature* matrix[10][10];
    int mat[10][10]; //count units
    int playerMat[10][10]; // не очаквах да са толкова много параметри и заради това не съм използвал вектор
    void SetPlayersUnits();
    void Clear(int row, int col);
public:
    Battlefield(Player* &player1, Player* &player2);
    bool BestPosition(int &sRow, int &sCol, int &dRow, int &dCol, int stamina = 0);
    bool IsFree(int row, int col);
    bool IsLose();
    void SetCreature(Creature* &unit, int &count, int &row, int &col, string player = " ");
    peir<Creature*, int, Player*> GetCreature(int &row, int &col);
    bool Move(int &sRow, int &sCol, int &dRow, int &dCol, int percent = 100);
    bool Attack(int &sRow, int &sCol, int &dRow, int &dCol, int percent = 100);
    void Print(string fileName = "output.txt");
    static double Distance(int sRow, int sCol, int dRow, int dCol);
    bool CheckDistanceForMove(int sRow, int sCol, int dRow, int dCol, int range = 0);
    bool CheckDistanceForAttack(int &sRow, int &sCol, int &dRow, int &dCol, int stamina = 0);
};

#endif /* defined(__OOP_Homework_Project__Battlefield__) */
