#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#define MOS 0

#define MAX_X 60
#define MAX_Y 60
#define MAX_Z 4

//size of sprites
#define SIZE_X 58
#define SIZE_Y 80

#define floorWidth 87
#define floorHeight 39
#define tileWidth 87
#define tileHeight 120
#define floorToFloor 73 //distance from floor to floor above.
#include "weapon.h"

class Game;
class Creature
{
    public:
        Creature();
        Creature(Game* pGame);
        sf::Sprite sprite;
        void setCharacter(Game *pGame);
        int getPositionX();
        int getPositionY();

        std::string behaviour;

        void move(int x, int y);
        void setPosition(int x, int y);
        int ap;
        int maxAp;

        int type; //Type of sprite
        void changeFacing(int i);

        int goHere(int x, int y, int z, int getMapData[MAX_Z][MAX_Y][MAX_X]);
        void moveNorth();
        void moveEast();
        void moveSouth();
        void moveWest();
        void moveNorthEast();
        void moveNorthWest();
        void moveSouthEast();
        void moveSouthWest();
        void moveUp();
        void moveDown();
        int getFacing();

        void loadCreature(std::string file);

        //These colliders are in terms on the map, not relative to one tile.
        int getCollisionNorth();
        int getCollisionSouth();
        int getCollisionEast();
        int getCollisionWest();
        int getCollisionUp();
        int getCollisionDown();

        bool noAmmo();

        void draw();
        Weapon weapon;

        //Autonomous Actions
        void charge(); //Human wave attacks and suicide rushes
        void moveTo(Creature other); //Move towards another creature
        void selectTarget(); //Select a target

        void aggressiveBehaviour();
        void PreservativeBehaviour();
        void mindlessBehaviour();

    protected:
        //Stats for humanoid characters
        int bravery;
        int accuracy;
        int strength;
        int health;
        int sight;
        //The sprites position
        int posX;
        int posY;
        //Last seen position
        int lPosX;
        int lPosY;
        //rank
        int ranking;
        //Which way the sprite is looking; 1 = North, 2 = North East... 5 = South- Continues clockwise
        //Increments by one
        int facing;
        //Crouching or Not
        bool crouching;
        //visibility
        bool isVisible;
        //name of humanoid
        std::string name;
        std::string mode;
        //dead or alive character
        bool dead;
        //Items in hand or inventory
        std::string leftHandItem;
        std::string rightHandItem;

        //collision fields...
        //...in terms of being in a 16*16*24 tile, independent of the map.
        //...origin at (0,0,0).
        int collisionNorth;
        int collisionSouth;
        int collisionEast;
        int collisionWest;
        int collisionUp;
        int collisionDown;

        int spriteOffset; //The position of the sprite in the character spritemap


    protected:
        Game* game;
        void updateSpritePosition();
        void updateSprite();
    public:
        int x;
        int y;
        int z;
};


#endif // CREATURE_H_INCLUDED
