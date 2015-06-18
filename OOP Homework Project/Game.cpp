#include "Game.h"
using namespace std;

bool BestPosition(Battlefield* &field, int &sRow, int &sCol, int &dRow, int &dCol);
Game::Game()
{
    m_player = new Player("Player");
    m_enemy = new Player("Enemy");
}

void Game::PrintUnitsPrice(Shop* &shop)
{
    for(auto elem : shop->Units())
    {
        cout << elem.first << " => " << elem.second << "\n";
    }
}

void Game::BaseMenu(string command)
{
    if(command == "start game")
    {
        GameMenu();
    }
    else if (command == "go in shop")
    {
        ShopMenu();
    }
    else if(command == "out")
    {
        
    }
}


void Game::ShopingUnits(Player* &player, Shop* &shop)
{
    int count;
    int random;
    map<string,int> units = shop->Units();
    
    int enemyGold = player->GetGold();
    int max = enemyGold/units["Griffon"];
    if (1 == Random(0, 1) && enemyGold >= units["Griffon"])
    {
        player->Buy(shop, new Griffon(), 1);
        enemyGold = player->GetGold();
    }
    
    max = enemyGold/units["Footman"];
    random = Random(0, 100);
    count = ((double)(max * random)/100 + 0.5);
    if (count > 0)
    {
        player->Buy(shop, new Footman(), count);
        enemyGold = player->GetGold();
    }
    
    
    max = enemyGold/units["Archer"];
    random = Random(0, 100);
    count = ((double)(max * random)/100 + 0.5);
    if (count > 0)
    {
        player->Buy(shop, new Archer(), count);
        enemyGold = player->GetGold();
    }
    
    max = enemyGold/units["Peasant"];
    player->Buy(shop, new Peasant(), max);
}

void Game::ShopMenu()
{
    Shop *shop = new Shop();
    int count;

    ShopingUnits(m_enemy, shop);
//    ShopingUnits(m_player, shop);
    
    
    
    {
        string name = "Player";
        cout<<"Name: ";
        getline(cin, name);
        cout<<name<<" is in shop"<<endl;
        m_player->SetName(name);
        
        string input;
        while (true)
        {
            cout<<"Command for shop:"<<endl;
            getline(cin, input);
            if (input[0] == 'b')//buy
            {
                switch (input[6])
                {
                    case 'a'://peasant
                        count = stoi(input.substr(11));
                        m_player->Buy(shop, new Peasant(), count);
                        break;
                    case 'c'://archer
                        count = stoi(input.substr(10));
                        m_player->Buy(shop, new Archer(), count);
                        break;
                    case 'o'://footman
                        count = stoi(input.substr(11));
                        m_player->Buy(shop, new Footman(), count);
                        break;
                    case 'i'://grifon
                        count = stoi(input.substr(11));
                        m_player->Buy(shop, new Griffon(), count);
                        break;
                    default:
                        break;
                }
            }
            else if (input[0] == 'p')//print
            {
                PrintUnitsPrice(shop);
            }
            else if (input[0] == 'g')//gold
            {
                cout<<m_player->GetGold()<<endl;
            }
            else break;
        }
    }
}
void Game::GameMenu()
{
    string input;
    Battlefield* field = new Battlefield(m_player,m_enemy);
    
    int sRow;
    int sCol;
    int dRow;
    int dCol;
    int percent;
    field->Print();
    while (true)
    {
        percent = 100;
        while (true)
        {
            cout<<"Command for game:"<<endl;
            getline(cin, input);
            
            if (input[0] == 'm')//move
            {
                sRow = (input[6] - '0');
                sCol = (input[8] - '0');
                dRow = (input[12] - '0');
                dCol = (input[14] - '0');
                
                if (input.size() > 16 && input[17] == '%')
                {
                    percent = stoi(input.substr(18));
                    if(percent > 100 || percent < 0)
                        percent = 100;
                }
                if( field->Move(sRow, sCol, dRow, dCol, percent) )
                    break;
                
            }
            else if (input[0] == 'a')//atack
            {
                sRow = (input[8] - '0');
                sCol = (input[10] - '0');
                dRow = (input[14] - '0');
                dCol = (input[16] - '0');
                
                if (input.size() > 18 && input[19] == '%')
                {
                    percent = stoi(input.substr(20));
                }
                
                if( field->Attack(sRow, sCol, dRow, dCol, percent) )
                    break;
                
                
            }
            else if (input[0] == 'n')//next round
            {
                break;
            }
            else if (input[0] == 's')//stop
            {
                break;
                return;
            }
            else if (input[0] == 'p') //print
            {
                string fileName = "output.txt";
                field->Print(fileName);
            }
            else
            {
                cout<<"error command"<<endl;
            }
        }

        if(field->IsLose())
        {
            break;
            return;
        }
        
        cout<<endl;
        AutoAttack(m_player, field);
//        AutoAttack(m_enemy, field);
        field->Print();
        cout<<endl;
        
        if(field->IsLose())
            return;
    }
}

void Game::AutoAttack(Player* &player, Battlefield* &field)
{
    Player* me = nullptr;
    vector< peir<int, int, int> > array;
    vector< peir<int, int, int> > array2;
    peir<int, int, int> element;
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            if(field->GetCreature(row, col).second != 0)
            {
                element.first = field->GetCreature(row, col).first->GetDamage()*
                                    field->GetCreature(row, col).second;
                element.second = row;
                element.third = col;
                
                if (field->GetCreature(row, col).third == player)
                {
                    array.push_back(element);
                }
                else
                {
                    if (me == nullptr)
                    {
                        me = field->GetCreature(row, col).third;
                    }
                    array2.push_back(element);
                }
            }
        }
    }
    
    int val1, val2, val3;
    int len = array.size();
    if (array2.size() > len)
    {
        len = array2.size();
    }
    for (int i = len; i >= 0; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (i < array.size() && array[j-1].first > array[j].first)
            {
                val1 = array[j-1].first;
                val2 = array[j-1].second;
                val3 = array[j-1].third;
                array[j-1] = array[j];
                array[j].first = val1;
                array[j].second = val2;
                array[j].third = val3;
            }
            
            
            if (i < array2.size() && array2[j-1].first < array2[j].first)
            {
                val1 = array2[j-1].first;
                val2 = array2[j-1].second;
                val3 = array2[j-1].third;
                array2[j-1] = array2[j];
                array2[j].first = val1;
                array2[j].second = val2;
                array2[j].third = val3;
            }
        }
    }
    
    if (field->GetCreature(array[0].second, array[0].third).first->GetHealth() == 0)
    {
        
        val1 = array[0].first;
        val2 = array[0].second;
        val3 = array[0].third;
        array[0] = array[array.size() - 1];
        array[array.size() - 1].first = val1;
        array[array.size() - 1].second = val2;
        array[array.size() - 1].third = val3;
    }
    if (field->CheckDistanceForAttack(array2[0].second, array2[0].third, array[0].second, array[0].third))
    {
        field->Attack(array2[0].second, array2[0].third, array[0].second, array[0].third);
//        cout<<"Attackkkkkk   "<<"row: "<<array2[0].second<<" col: "<<array2[0].third<<endl;
    }
    else
    {
        int sRow = array2[0].second;
        int sCol = array2[0].third;
        
        int fRow = array[0].second;
        int fCol = array[0].third;
        
        int dRow = fRow;
        int dCol = fCol;
        
        int range = field->GetCreature(sRow, sCol).first->GetStamina();
        
        while(true)
        {
            
            field->BestPosition(sRow, sCol, dRow, dCol, range);
            if(
               field->CheckDistanceForMove(sRow, sCol, dRow, dCol) )
            {
                field->Move(sRow, sCol, dRow, dCol);
                
                break;
            }
            else
            {
                range++;
            }
            
        }
    }
}
