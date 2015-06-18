#ifndef __OOP_Homework_Project__Creature__
#define __OOP_Homework_Project__Creature__

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
using namespace std;

class Creature
{
protected:
    int damage;
    int defense;
    int health;
    int mana;
    int stamina;
    int critChance;
    int range;
    string type;
public:
    Creature(int damage = 0, int defense = 0, int health = 0, int mana = 0, int stamina = 0, int critChance = 0, int range = 0);
    virtual string GetType();
    void SetDamage(int damage);
    int GetDamage();
    void SetDefense(int defense);
    int GetDefense();
    void SetHealth(int health);
    int GetHealth();
    void SetMana(int mana);
    int GetMana();
    void SetStamina(int stamina);
    int GetStamina();
    void SetRange(int range);
    int GetRange();
    void SetCritChance(int critChance);
    int GetCritChance();
    
    virtual int Attack(int count);
    virtual int Defense(int count, int dmg);
};

int Random(int min, int max);

class Peasant:public Creature
{
public:
    Peasant(int damage = 1, int defense = 0, int health = 5, int mana = 0, int stamina = 3, int critChance = 20, int range = 3)
    :Creature(damage, defense, health, mana, stamina, critChance, range)
    {
        type = "Peasant";
    }
    string GetType()
    {
        return type;
    }
//    void Attack(Creature* &unit, int &count)
//    void Attack(int &count)
//    {
////        int random = Random(0, 100);
////        if (random <= this->GetCritChance())
////        {
////            <#statements#>
////        }
//    }
//    void Move()
//    {
//        
//    }
};

class Footman:public Creature
{
public:
    Footman(int damage = 3, int defense = 2, int health = 7, int mana = 0, int stamina = 4, int critChance = 30, int range = 3)
    :Creature(damage, defense, health, mana, stamina, critChance, range)
    {
        
        type = "Peasant";
    }
    string GetType()
    {
        return "Footman";
    }
//    void Attack()
//    {
//        
//    }
//    void Move()
//    {
//        
//    }
};

class Archer:public Creature
{
public:
    Archer(int damage = 2, int defense = 1, int health = 5, int mana = 0, int stamina = 3, int critChance = 20, int range = 3)
    :Creature(damage, defense, health, mana, stamina, critChance, range)
    {
        
    }
    string GetType()
    {
        return "Archer";
    }
//    void Attack()
//    {
//        
//    }
//    void Move()
//    {
//        
//    }
};

class Griffon:public Creature
{
public:
    Griffon(int damage = 4, int defense = 3, int health = 10, int mana = 0, int stamina = 2, int critChance = 30, int range = 3)
    :Creature(damage, defense, health, mana, stamina, critChance, range)
    {
        
    }
    string GetType()
    {
        return "Griffon";
    }
};

class Hero:public Creature
{
public:
    Hero(int damage = 2, int defense = 0, int health = 0, int mana = 5, int stamina = 1000, int critChance = 35, int range = 0)
    :Creature(damage, defense, health, mana, stamina, critChance, range)
    {

    }
    string GetType()
    {
        return "Hero";
    }
    int Defense(int count, int dmg)
    {
        return 1;
    }
//    void Attack()
//    {
//        
//    }
//    void Move()
//    {
//        
//    }
};



#endif