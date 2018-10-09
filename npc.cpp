#include "npc.h"
#include "game.h"

Npc::Npc()
{

}

Npc::Npc(Game* pGame)
{
    std::cout << "Creature Initialized" << std::endl;
    game = pGame; //Set the pointer to the current game
    type = MOS;
    sprite.setTexture(game->resourceManager.characterTextures);
    sprite.setTextureRect(sf::IntRect(0,0,60,80));
    x=1;
    y=1;
    z=0;
    moveSouthEast();
    updateSpritePosition();
    sprite.setOrigin(30,0);
    facing = 0;

    weapon.loadWeapon("TESTRIFLE.wep");
    weapon.loadAmmo("TEST.ammo");
}

void Npc::loadNpc(std::string file)
{
    std::ifstream getData;
    getData.open(file.c_str());
    getData >> this->name;
    getData >> this->health;
    getData.close();

    std::cout << "---NEW NPC LOADED---" << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Health: " << this->health << std::endl;


}


/*
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
*/
