#include "weapon.h"

bool Weapon::isEmpty()
{
    if (ammo.amount == 0)
        return true;
    return false;
}

void Weapon::loadWeapon(std::string file)
{
    std::ifstream getData;
    //TEST
    getData.open(file.c_str());
    //This is the order in which the data is retriebed
    getData >> this->name;
    getData >> this->maxAmmo;
    getData >> this->damage;
    getData >> this->accuracyBonus;
    getData >> this->acceptedAmmo;
    getData >> this->modifier;
    getData >> this->fireMode;
    getData.close();

    std::cout << "--NEW WEAPON LOADED--" << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "MaxAmmo: " << this->maxAmmo << std::endl;
    std::cout << "Damage: " << this->damage << std::endl;
    std::cout << "AccuracyBonus: " << this->accuracyBonus << std::endl;
    std::cout << "AcceptedType: " << this->acceptedAmmo << std::endl;
    std::cout << "FireMode: " << this->fireMode << std::endl;
    std::cout << std::endl;
}

void Weapon::loadAmmo(std::string file)
{
    std::ifstream getData;
    //TEST
    getData.open(file.c_str());
    //This is the order in which the data is retriebed
    getData >> this->ammo.name;
    getData >> this->ammo.amount;
    getData >> this->ammo.damage;
    getData >> this->ammo.modifier;
    getData >> this->ammo.type;
    getData.close();

    std::cout << "--NEW AMMUNITION LOADED--" << std::endl;
    std::cout << "Name: " << this->ammo.name << std::endl;
    std::cout << "Amount: " << this->ammo.amount << std::endl;
    std::cout << "Damage: " << this->ammo.damage << std::endl;
    std::cout << "Modifier: " << this->ammo.modifier << std::endl;
    std::cout << "Type: " << this->ammo.type << std::endl;
    std::cout << std::endl;
}

