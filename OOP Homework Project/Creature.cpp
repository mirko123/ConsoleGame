#include "Creature.h"
using namespace std;

Creature::Creature(int damage, int defense, int health, int mana, int stamina, int critChance, int range)
{
    SetDamage(damage);
    SetDefense(defense);
    SetHealth(health);
    SetMana(mana);
    SetStamina(stamina);
    SetCritChance(critChance);
    SetRange(range);
}
string Creature::GetType()
{
    return type;
}
void Creature::SetDamage(int damage)
{
    if (damage < 0) {
        cout<<"damage need be >= 0"<<endl;
    }
    else
        this->damage = damage;
}
int Creature::GetDamage()
{
    return this->damage;
}

void Creature::SetDefense(int defense)
{
    if (defense < 0) {
        cout<<"defense need be >= 0"<<endl;
    }
    else
        this->defense = defense;
}
int Creature::GetDefense()
{
    return this->defense;
}

void Creature::SetHealth(int health)
{
    if (health < 0) {
        cout<<"health need be >= 0"<<endl;
    }
    else
        this->health = health;
}
int Creature::GetHealth()
{
    return this->health;
}

void Creature::SetMana(int mana)
{
    if (mana < 0) {
        cout<<"mana need be >= 0"<<endl;
    }
    else
        this->mana = mana;
}
int Creature::GetMana()
{
    return this->mana;
}

void Creature::SetStamina(int stamina)
{
    if (stamina < 0) {
        cout<<"stamina need be >= 0"<<endl;
    }
    else
    {
        this->stamina = stamina;
    }
}
int Creature::GetStamina()
{
    return this->stamina;
}

void Creature::SetRange(int range)
{
    if (range < 0) {
        cout<<"range need be >= 0"<<endl;
    }
    else
    {
        this->range = range;
    }
}
int Creature::GetRange()
{
    return this->range;
}

void Creature::SetCritChance(int critChance)
{
    if (critChance < 0) {
        cout<<"critChance need be >= 0"<<endl;
    }
    else
        this->critChance = critChance;
}
int Creature::GetCritChance()
{
    return this->critChance;
}

int Creature::Attack(int count)
{
    int crits = 0;
    for (int i = 0; i < count; i++)
    {
        if (Random(0, 100) <= critChance)
        {
            crits++;
        }
    }
    int dmg = crits*damage + count*damage;
    return dmg;
}
int Creature::Defense(int count, int dmg)
{
    int allHp = health*count;
    int loseHp = (dmg - defense*(dmg/health));
    if(loseHp > 0) allHp = allHp - loseHp;
    if(allHp <= 0) return 0;
    else
    {
        return allHp/health;
    }
}


int Random(int min, int max)
{
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range
    
    return distr(eng); // generate numbers
}

