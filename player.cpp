#include "player.h"
#include "game.h"

Player::Player(Game* pGame)
{
    std::cout << "Creature Initialized" << std::endl;
    game = pGame; //Set the pointer to the current game
    type = MOS;
    sprite.setTexture(game->resourceManager.characterTextures);
    sprite.setTextureRect(sf::IntRect(0,0,60,80));
    x=12;
    y=12;
    z=0;
    moveSouthEast();
    updateSpritePosition();
    sprite.setOrigin(30,0);
    facing = 0;

    weapon.loadWeapon("TESTRIFLE.wep");
    weapon.loadAmmo("TEST.ammo");
}
