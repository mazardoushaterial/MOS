#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>
#include "ammunition.h"


class Weapon
{
  public:
    bool isEmpty(); // returns true if no ammunition is left
    void loadWeapon(std::string name);
    void loadAmmo(std::string name);
    Ammunition ammo;
  private:
    std::string name;
    int maxAmmo;
    int damage;
    int accuracyBonus;
    std::string acceptedAmmo; //Accepted ammo type
    std::string modifier; //Special stat
    std::string fireMode; //3rnd burst, full auto, single fire, etc.
    int meleeDamage;
};


#endif // WEAPON_H_INCLUDED
