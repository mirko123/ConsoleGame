//
//  Battlefield.cpp
//  OOP Homework Project
//
//  Created by Мирослав Николов on 25.05.15.
//  Copyright (c) 2015 г. Мирослав Николов. All rights reserved.
//

#include "Battlefield.h"
#include <iostream>
#include <fstream>

Battlefield::Battlefield(Player* &player1, Player* &player2)
{
    this->player1 = player1;
    this->player2 = player2;
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            matrix[row][col] = nullptr;
            mat[row][col] = 0;
            playerMat[row][col] = 0;
        }
        
        
        if(row < player1->GetUnits().size())
        {
            matrix[row][0] = player1->GetUnits()[row].first;
            mat[row][0] = player1->GetUnits()[row].second;
            playerMat[row][0] = 1;
        }
        if(row < player2->GetUnits().size())
        {
            matrix[row][9] = player2->GetUnits()[row].first;
            mat[row][9] = player2->GetUnits()[row].second;
            playerMat[row][9] = -1;
        }
    }
}

void Battlefield::SetCreature(Creature* &unit,int &count, int &row, int &col, string player)
{
    if ( IsFree(row, col))
    {
        matrix[row][col] = unit;
        mat[row][col] = count;
        if (player[0] == 'e')
        {
            playerMat[row][col] = -1;
        }
        else
        {
            playerMat[row][col] = 1;
        }
    }
    else
    {
        cout<<"this position is occupied"<<endl;
    }
}
peir<Creature*, int, Player* > Battlefield::GetCreature(int &row, int &col)
{
    peir<Creature*, int, Player*> peir(matrix[row][col], mat[row][col]);
    if (playerMat[row][col] == 1)
    {
        peir.third = player1;
    }
    else if (playerMat[row][col] == -1) peir.third = player2;
    return peir;
}

double Battlefield::Distance(int sRow, int sCol, int dRow, int dCol)
{
    return sqrt((dRow - sRow)*(dRow - sRow) + (dCol - sCol)*(dCol - sCol));;
}

bool Battlefield::CheckDistanceForMove(int sRow, int sCol, int dRow, int dCol, int range)
{
    int distance = sqrt((dRow - sRow)*(dRow - sRow) + (dCol - sCol)*(dCol - sCol));
    if (range == 0)
    {
        range = matrix[sRow][sCol]->GetRange();
    }
    if (distance > matrix[sRow][sCol]->GetRange())
    {
        return 0;
    }
    else return 1;
}
bool Battlefield::CheckDistanceForAttack(int &sRow, int &sCol, int &dRow, int &dCol, int stamina)
{
    int distance = sqrt((dRow - sRow)*(dRow - sRow) + (dCol - sCol)*(dCol - sCol));
    if (stamina == 0)
    {
        stamina = matrix[sRow][sCol]->GetStamina();
    }
    if (distance > matrix[sRow][sCol]->GetStamina())
    {
        return 0;
    }
    else return 1;
}

bool Battlefield::IsLose()
{
    if(player1->GetUnits().size() == 1 && player2->GetUnits().size() == 1)
    {
        cout<<"Both Players lose."<<endl;
        return 1;
    }
    else if(player1->GetUnits().size() == 1)
    {
        cout<<player1->GetName()<<" lose."<<endl;
        player2->AddGold(player1->GetGold());
        return 1;
    }
    else if(player2->GetUnits().size() == 1)
    {
        player1->AddGold(player2->GetGold());
        cout<<player2->GetName()<<" lose."<<endl;
        return 1;
    }
    
    return 0;
}

bool Battlefield::Move(int &sRow, int &sCol, int &dRow, int &dCol, int percent)
{
    if(!IsFree(sRow, sCol) && (sRow != dRow || sCol != dCol))
    {
        int willMove = double(mat[sRow][sCol] * double((double)percent/100));
        int willStay = mat[sRow][sCol] - willMove;

        if (!CheckDistanceForMove(sRow, sCol, dRow, dCol))
        {
            cout<<"Big distance"<<endl;
            return 0;
        }
        else if (!IsFree(dRow, dCol))
        {
            if(playerMat[sRow][sCol] == playerMat[dRow][dCol] &&
                    matrix[sRow][sCol]->GetType() == matrix[dRow][dCol]->GetType())
            {
                matrix[dRow][dCol] = matrix[sRow][sCol];
                mat[dRow][dCol] = mat[sRow][sCol];
                playerMat[dRow][dCol] = playerMat[sRow][sCol];
                
                if (willStay == 0)
                {
                    matrix[sRow][sCol] = nullptr;
                    mat[dRow][dCol] += mat[sRow][sCol];
                    mat[sRow][sCol] = 0;
                    playerMat[sRow][sCol] = 0;
                }
                else
                {
                    mat[sRow][sCol] = willStay;
                    mat[dRow][dCol] += willMove;
                }
                return 1;
            }
            
            cout<<"error source position"<<endl;
            return 0;
        }
        else if (IsFree(dRow, dCol))
        {
            
            matrix[dRow][dCol] = matrix[sRow][sCol];
            mat[dRow][dCol] = mat[sRow][sCol];
            playerMat[dRow][dCol] = playerMat[sRow][sCol];
            
            if (willStay == 0)
            {
                matrix[sRow][sCol] = nullptr;
                mat[dRow][dCol] = mat[sRow][sCol];
                mat[sRow][sCol] = 0;
                playerMat[sRow][sCol] = 0;
            }
            else
            {
                mat[sRow][sCol] = willStay;
                mat[dRow][dCol] = willMove;
            }
            return 1;
        }
        else
        {
            cout<<"error destionation"<<endl;
            return 0;
        }
    }
    else
    {
        cout<<"nqma nikoi"<<endl;
        return 0;
    }
}
//Miro
//buy archer 1
//buy grifon 1
//buy footer 1
//
//move (0,0) (2,2)
//attack (2,2) (3,3)
bool Battlefield::Attack(int &sRow, int &sCol, int &dRow, int &dCol, int percent)
{
    int fRow = dRow;
    int fCol = dCol;
    bool check = !IsFree(dRow, dCol) && playerMat[dRow][dCol] != playerMat[sRow][sCol]
        && (this->CheckDistanceForAttack(sRow, sCol, fRow, fCol) || BestPosition(sRow, sCol, dRow, dCol));
  
    if(check)
    {
        int aDmg = 0;
        int aCount = 0;
        
        int dDmg = 0;
        int dCount = 0;
        
        
        if(matrix[fRow][fCol]->GetType() == "Hero")
        {
            cout<<"Cant attack Hero."<<endl;
            return 0;
        }
        else if(matrix[sRow][sCol]->GetType() == "Hero")
        {
            aDmg = matrix[sRow][sCol]->GetDamage();
            dCount = matrix[fRow][fCol]->Defense(mat[fRow][fCol], aDmg);
            if (dCount == 0)
            {
                Clear(fRow, fCol);
            }
            else mat[fRow][fCol] = dCount;
            
            cout<<"attack player Damage: "<<aDmg<<endl;
            cout<<"defense player units: "<<dCount<<endl;
            cout<<endl;
            
            SetPlayersUnits();
            
            return 1;
        }
        if(this->CheckDistanceForAttack(sRow, sCol, fRow, fCol) ||
           this->Move(sRow, sCol, dRow, dCol, percent))
        {
            //......
            while (true)
            {
                if(dRow == fRow && dCol == fCol)
                {
                    dRow = sRow;
                    dCol = sCol;
                }
                
                aDmg = this->matrix[dRow][dCol]->Attack(mat[dRow][dCol]);
                dDmg = this->matrix[fRow][fCol]->Attack(mat[fRow][fCol]);
                
                
                aCount = this->matrix[dRow][dCol]->Defense(mat[dRow][dCol], dDmg);
                dCount = this->matrix[fRow][fCol]->Defense(mat[fRow][fCol], aDmg);
                
                cout<<"attack player Damage: "<<aDmg<<endl;
                cout<<"attack player units: "<<aCount<<endl;
                cout<<"defense player Damage: "<<dDmg<<endl;
                cout<<"defense player units: "<<dCount<<endl;
                cout<<endl;
                
                mat[dRow][dCol] = aCount;
                mat[fRow][fCol] = dCount;
                
                
                
                if (dCount == 0 && aCount == 0)
                {
                    cout<<"both player lose units"<<endl;

                    Clear(fRow, fCol);
                    Clear(dRow, dCol);
                    
                    
                    break;
                }
                else if (aCount == 0)
                {
                    if(playerMat[dRow][dCol] == 1)
                        cout<<player1->GetName()<<" Lose units"<<endl;
                    else if(playerMat[dRow][dCol] == -1)
                        cout<<player2->GetName()<<" Lose units"<<endl;
                    else cout<<"error__"<<endl;
                    
                    Clear(dRow, dCol);
                    
                    break;
                }
                else if (dCount == 0)
                {
                    if(playerMat[fRow][fCol] == 1)
                        cout<<player1->GetName()<<" Lose units"<<endl;
                    else if(playerMat[fRow][fCol] == -1)
                        cout<<player2->GetName()<<" Lose units"<<endl;
                    else cout<<"error__"<<endl;

                    Clear(fRow, fCol);
                    break;
                }
            }
            
            SetPlayersUnits();
            
            return 1;
        }
        else
        {
            cout<<"Big distance"<<endl;
        }
    }
    else
    {
        cout<<"nqma nikoi tam"<<endl;
    }
    return 0;
}

bool Battlefield::IsFree(int row, int col)
{
    if (matrix[row][col] == nullptr) {
        return true;
    }
    else return false;
}

void Battlefield::Clear(int row, int col)
{
    matrix[row][col] = nullptr;
    mat[row][col] = 0;
    playerMat[row][col] = 0;
}

void Battlefield::Print(string fileName)
{
    string field;
    string value = "";
    string prefix;
    int len = 0;
    
    map<string, int> map;

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            value = to_string(mat[row][col]);
            if (mat[row][col] != 0)
            {
                value = value + matrix[row][col]->GetType()[0];
                
                if (playerMat[row][col] == -1)
                {
                    value = 'E' + value;
                    prefix = "E" + string(&matrix[row][col]->GetType()[0]);
                    map[prefix]+=mat[row][col];
                }
                else if (playerMat[row][col] == 1)
                {
                    value = 'M' + value;
                    prefix = "M" + string(&matrix[row][col]->GetType()[0]);
                    map[prefix]+=mat[row][col];
                }
            }
            
            len = value.length();
            for (int i = 0; i < 7 - len; i++) {
                value += " ";
            }
            field = field + value;
        }
        field+='\n';
    }
    cout<<field;
    
    for(auto it = map.begin(); it != map.cend(); ++it)
    {
        field = field + it->first + "-" + to_string(it->second) + " ";
    }
    
    ofstream outfile (fileName);
    outfile << field << endl;
    outfile.close();
}

void Battlefield::SetPlayersUnits()
{
    vector< pair<Creature*, int> > playerUnits1;
    vector< pair<Creature*, int> > playerUnits2;
    pair<Creature*, int> pair;
    
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            if (playerMat[row][col] == 1)
            {
                if (playerUnits1.size() > 0)
                {
                    for (int i = 0; i<playerUnits1.size(); i++)
                    {
                        if(i == playerUnits1.size()-1)
                        {
                            pair.first = matrix[row][col];
                            pair.second = 1;
                            playerUnits1.push_back(pair);
                            break;
                        }
                        else if (playerUnits1[i].first->GetType() == matrix[row][col]->GetType())
                        {
                            playerUnits1[i].first = playerUnits1[i].first + mat[row][col];
                        }
                    }
                }
                else if(playerUnits1.size() == 0)
                {
                    pair.first = matrix[row][col];
                    pair.second = mat[row][col];
                    playerUnits1.push_back(pair);
                }
                else cout<<"big error"<<endl;
                
            }
            //attack (0,0) (0,9)
            
            else if (playerMat[row][col] == -1)
            {
                
                
                if (playerUnits2.size() > 0)
                {
                    for (int i = 0; i<playerUnits2.size(); i++)
                    {
                        
                        if(i == playerUnits2.size()-1)
                        {
                            pair.first = matrix[row][col];
                            pair.second = 1;
                            playerUnits2.push_back(pair);
                            break;
                        }
                        else if (playerUnits2[i].first->GetType() == matrix[row][col]->GetType())
                        {
                            playerUnits2[i].first = playerUnits2[i].first + mat[row][col];
                        }
                    }
                }
                else if(playerUnits2.size() == 0)
                {
                    pair.first = matrix[row][col];
                    pair.second = mat[row][col];
                    playerUnits2.push_back(pair);
                }
                else cout<<"big error"<<endl;

            }
        }
    }
    
    
    player1->SetPlayerUnits(playerUnits1);
    player2->SetPlayerUnits(playerUnits2);
    
    
//    for (int i = 0; i<playerUnits1.size(); i++)
//    {
//        cout<<playerUnits1[i].first->GetType()<<" => "<<playerUnits1[i].second<<endl;
//    }
//    cout<<endl;
//    
//    for (int i = 0; i<playerUnits2.size(); i++)
//    {
//        cout<<playerUnits2[i].first->GetType()<<" => "<<playerUnits2[i].second<<endl;
//    }
}

bool Battlefield::BestPosition(int &sRow, int &sCol, int &dRow, int &dCol, int stamina)
{
    int fRow = dRow;
    int fCol = dCol;
    
    if(stamina == 0) stamina = this->matrix[sRow][sCol]->GetStamina();
    
    int distance = 100;
    
    bool check = false;
    
    for (int row = fRow - stamina; row < fRow + stamina; row++)
    {
        if (row >= 0 && row < 10)
        {
            for (int col = fCol - stamina; col < fCol + stamina; col++)
            {
                if (col >= 0 && col < 10 && !(col == fCol && row == fRow))
                {
                    if( this->IsFree(row, col) && distance > this->Distance(sRow, sCol, row, col) )
                    {
                        distance = this->Distance(sRow, sCol, dRow, dCol);
                        dRow = row;
                        dCol = col;
                        check = true;
                    }
                }
            }
        }
    }
    if (!check)
    {
        cout<<"cant atack"<<endl;
    }
    
    return check;
}


