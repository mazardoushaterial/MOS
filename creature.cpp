#include "djikstra.h"
#include "creature.h"
#include "game.h"
#include <iostream>

Creature::Creature()
{
    std::cout << "Temporary construction" << std::endl;
}

Creature::Creature(Game* pGame)
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
}

void Creature::draw()
{
    game->renderWindow.draw(sprite);
}

int Creature::goHere(int x, int y, int z, int getMapData[MAX_Z][MAX_Y][MAX_X])
{
    int direction = djikstra(this->x,this->y,this->z,x,y,z,getMapData);
    if (direction == 0)
    {
       moveSouthEast();
    }
    else if (direction == 1)
    {
        moveSouth();
    }
    else if (direction == 2)
    {
        moveSouthWest();
    }
    else if (direction == 3)
    {
        moveWest();
    }
    else if (direction == 4)
    {
        moveNorthWest();
    }
    else if (direction == 5)
    {
        moveNorth();
    }
    else if (direction == 6)
    {
        moveNorthEast();
    }
    else if (direction == 7)
    {
        moveEast();
    }
    else if (direction == 8)
    {
        moveDown();
    }
    else if (direction == 9)
    {
        moveUp();
    }
    changeFacing(direction);
}

void Creature::changeFacing(int i)
{
    if (i == 0)
    {
        sprite.setTextureRect(sf::IntRect(4*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 4;
    }
    else if (i == 1)
    {
        sprite.setTextureRect(sf::IntRect(5*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 5;
    }
    else if (i == 2)
    {
        sprite.setTextureRect(sf::IntRect(6*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 6;
    }
    else if (i == 3)
    {
        sprite.setTextureRect(sf::IntRect(7*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 7;
    }
    else if (i == 4)
    {
        sprite.setTextureRect(sf::IntRect(0*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 0;
    }
    else if (i == 5)
    {
        sprite.setTextureRect(sf::IntRect(1*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 1;
    }
    else if (i == 6)
    {
        sprite.setTextureRect(sf::IntRect(2*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 2;
    }
    else if (i == 7)
    {
        sprite.setTextureRect(sf::IntRect(3*SIZE_X,type*SIZE_Y,SIZE_X,SIZE_Y));
        facing = 3;
    }

}

void Creature::moveNorth(){ move(0,-1); }
void Creature::moveEast(){ move(1,0); }
void Creature::moveSouth(){ move(0,1); }
void Creature::moveWest(){ move(-1,0); }
void Creature::moveNorthEast(){ move(1,-1);}
void Creature::moveNorthWest(){ move(-1,-1); }
void Creature::moveSouthEast(){ move(1,1) ;}
void Creature::moveSouthWest(){ move(-1,1) ;}
void Creature::moveDown()
{
    this->z--;
    updateSpritePosition();
}
void Creature::moveUp()
{
    this->z++;
    updateSpritePosition();
}

void Creature::move(int x, int y)
{
    this->x += x;
    this->y += y;
    updateSpritePosition();
}

void Creature::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    updateSpritePosition();
}

void Creature::updateSpritePosition()
{
    this->sprite.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (z*floorToFloor));
}

int Creature::getPositionX()
{
    return x;
}

int Creature::getPositionY()
{
    return y;
}
