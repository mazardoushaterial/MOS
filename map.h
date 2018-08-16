#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "floor.h"
#include "cursor.h"
//#include "LOFMap.h"
#include "octants.h"
#include "DDA.h"
//#include "djikstra.h"

#define floorWidth 87
#define floorHeight 39
#define tileWidth 87
#define tileHeight 120
#define floorToFloor 73 //distance from floor to floor above.


class Game;
class Map
{
    public:
        Map(Game * pGame);
        //map has...
        Tile tile[MAX_Z][MAX_Y][MAX_X]; //Walls, trees, fences... blockables
        Floor floor[MAX_Z][MAX_Y][MAX_X]; //Floor tiles... walkables
        bool visible[MAX_Z][MAX_Y][MAX_X]; //check if the tile is visible
        int walkMap[MAX_Z][MAX_Y][MAX_X];
        void drawTile(int x, int y, int z);
        void drawFloor(int x, int y, int z);
        void draw();
        sf::View view;
        void increaseHeight();
        void decreaseHeight();
        void loadMap();
        void configureWalkMap();
        int getCurrentHeight();
        void setVisible(int x, int y, int z);

    private:
        bool outOfBounds(int x, int y, int z);
        Game * game;
        int height;
        sf::Texture mapTexture;
        void setUpTiles();
        void setUpFloor();
    public:
        //Octants rayCaster;
        //LOFMap lof;
        DDA raycaster;
    public:
        sf::Sprite stamper;

    //OCTANTS STUFF
    public:

        bool tileOutOfBounds(int x, int y, int z);
        //void draw(int w, int s)
        void drawOctant(int playerW, int playerS, int playerZ, int octant);
        void drawOctants(int x, int y, int z, int facing);

};

#endif // MAP_H_INCLUDED
