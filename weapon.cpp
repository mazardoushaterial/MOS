#include "weapon.h"

bool Weapon::isEmpty()
{
    if (ammo == 0)
        return true;
    return false;
}

void Weapon::loadWeapon(std::string name)
{
    std::ifstream getMap;
    std::string outputName;
    //TEST
    getMap.open(name.c_str());
    getMap >> outputName;
    std::cout << outputName << std::endl;
    std::cout << name << std::endl;
    std::cout << name.c_str() << std::endl;
    getMap.close();
}
