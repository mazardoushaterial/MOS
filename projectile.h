#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include "weapon.h"
#include <cmath>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#define floorWidth 87
#define floorHeight 39
#define tileWidth 87
#define tileHeight 120
#define floorToFloor 73 //distance from floor to floor above.

//
//The physical projectile in the game
//
class Projectile
{
    public:
        Projectile();
        Projectile(sf::Texture pTexture);

        //Set the projectile to the weapon's stats
        void setWeapon(Weapon weapon);

        //get position of the object
        void setPosition(int x, int y, int z);
        //Rounded position
        int getRoundPositionX();
        int getRoundPositionY();
        int getRoundPositionZ();
        //Float version of position
        float getRawPositionX();
        float getRawPositionY();
        float getRawPositionZ();
        int getVecX();
        int getVecY();
        int getVecZ();
        void stopMoving();
        void startMoving();
        bool outOfBounds();
        bool isMoving(); //check if the projectile is destroyed or not
        //void fire(int x1, int y1, int z1, int x2, int y2, int z2);
        void update();
        void move();
        void shoot(int x1, int y1, int z1, int x2, int y2, int z2);
        void setTrajectory(float x, float y, float z);
        void draw(sf::RenderWindow &renderWindow);
        void setSpritePosition(float x, float y);
        void setSpriteToTilePosition(); //Go from collision Coord to Tile coord
        int getTileCoord(float a);
    protected:

        sf::Sprite sprite;
        sf::Texture texture;

        //where it is
        float x;
        float y;
        float z;


        //Where it's moving
        float vecX;
        float vecY;
        float vecZ;

        bool moving;
    };

#endif // PROJECTILE_H_INCLUDED
