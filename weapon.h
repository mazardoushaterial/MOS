#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>

#define NONE 0
#define BALLISTIC 1
#define FIRE 2
#define LASER 3

class Weapon
{
  public:
    bool isEmpty(); // returns true if no ammunition is left
    void loadWeapon(std::string name);
  private:
    int ammo;
    int maxAmmo;
};


#endif // WEAPON_H_INCLUDED
