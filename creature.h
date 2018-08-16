#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED
#include <SFML/Graphics.hpp>

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

class Game;
class Creature
{
    public:
        Creature();
        Creature(Game* pGame);
        sf::Sprite sprite;
        int getPositionX();
        int getPositionY();

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

        void draw();

    public:
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
