#ifndef DDA_H_INCLUDED
#define DDA_H_INCLUDED
#include "LOFMap.h"
#include <iostream>
#define MAP_X 16*60
#define MAP_Y 16*60
#define MAP_Z 24*4
class DDA
{
    public:
        DDA();
        //bool board[MAP_Z][MAP_Y][MAP_X];
        bool voxelMap[MAP_Z][MAP_Y][MAP_X];
        void setUpVoxelMap(std::string tileBoard[4][60][60]);
        void setBoard(bool pBoard[MAP_Z][MAP_Y][MAP_X]);
        void drawTiles();
        float abs(float a);
        int round(float n);
        void putTile(int x, int y, int z);
        //In conjuction with the octants, and the LOF, cast a ray and see if it makes it to the target location
        bool castRay(int x1, int y1, int z1, int x2, int y2, int z2);
        bool isTileVisible(int objectX, int objectY, int objectZ, int targetX, int targetY, int targetZ);
        bool isTileVisibleOptimised(int objectX, int objectY, int objectZ, int targetX, int targetY, int targetZ);
    private:
        LOFMap lof;
};

#endif // DDA_H_INCLUDED
