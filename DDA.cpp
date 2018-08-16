#include "DDA.h"


/*
void DDA::setBoard(bool pBoard[MAP_Z][MAP_Y][MAP_X])
{
    for (int z = 0 ; z < MAP_Z; z++)
    {
        for (int x = 0; x < MAP_X; x++)
        {
            for (int y = 0; y < MAP_Y; y++)
            {
                if(pBoard[z][y][x] == 1)
                {
                    board[z][y][x] = 1;
                }
                else if(pBoard[z][y][x] == 0)
                {
                    board[z][y][x] = 0;
                }
            }
        }
    }
}
*/

/*
void DDA::drawTiles()
{
    for (int z = 0 ; z < MAP_Z; z++)
    {
        for (int y = 0; y < MAP_Y; y++)
        {
            for (int x = 0; x < MAP_X; x++)
            {
                if (board[z][y][x] == 1)
                {
                    std::cout << "x";
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
*/

DDA::DDA()
{

    //temporarySetUpPlace
    lof.loadLOFMaps();
}

void DDA::setUpVoxelMap(std::string tileBoard[4][60][60])
{

    for (int z = 0; z < 4; z++)
    {
        for (int y = 0; y < 60; y++)
        {
            for (int x = 0; x < 60; x++)
            {
                for (int vz = 0; vz < 24; vz++)
                {
                    for (int vy = 0; vy < 16; vy++)
                    {
                        for (int vx = 0; vx < 16; vx++)
                        {
                            //change ALL of this after
                            if (tileBoard[z][y][x] == "str_concrete1" || tileBoard[z][y][x] == "str_concrete2"
                                || tileBoard[z][y][x] == "str_concrete3" || tileBoard[z][y][x] == "str_concrete4"
                                || tileBoard[z][y][x] == "str_concrete5" || tileBoard[z][y][x] == "str_concrete6"
                                || tileBoard[z][y][x] == "str_concrete7" || tileBoard[z][y][x] == "str_concrete0"
                                || tileBoard[z][y][x] == "wall")
                            {
                                    //Change this aswell ("full")
                                voxelMap[z*24 + vz][y*16 + vy][x*16 + vx] = lof.full[vz][vy][vx];
                            }
                        }
                    }
                }
        }
    }
    }
}

float DDA::abs(float a)
{
    if (a < 0)  //If less than zero
        return 0-a; //Flip sign
    else
        return a;   //Return original value
}

int DDA::round(float n)
{
    if((n+0.5)>=(int(n)+1))
    {
    n = int(n+1);
    }
    else
    {
    n = int(n);
    }
    return n;
}

void DDA::putTile(int x, int y, int z)
{
//    board[z][y][x] = 1;
    return;
}

bool DDA::castRay(int x1, int y1, int z1, int x2, int y2, int z2)
{
    //setBoard(pBoard);
    int steps;
    float dx, dy, dz, incX, incY, incZ, x = x1, y = y1, z = z1;
    dx = x2-x1;
    dy = y2-y1;
    dz = z2-z1;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
        if (abs(dz) > abs(dx))
        {
            steps = abs(dz);
        }
    }
    else
    {
        steps = abs(dy);
        if (abs(dz) > abs(dy))
        {
            steps = abs(dz);
        }
    }
    incX = dx / (float)steps;
    incY = dy / (float)steps;
    incZ = dz / (float)steps;
    for (int i = 0; i < steps; i++)
    {
        x = x + incX;
        y = y + incY;
        z = z + incZ;
        if(round(x) == x2 && round(y) == y2 && round(z) == z2)
        {
            //keep going
        }
        else if(voxelMap[round(z)][round(y)][round(x)] == true) //&& (round(x) != x2 && round(y) != y2 && round(z) != z2)) //If the ray was blocked, by anything but the target (hitting the target is ideal)
        {
            return false;
        }
        //putTile(round(x),round(y),round(z));
    }
    //Passing the ray check test means it successfully made it to target
    return true;
}

bool DDA::isTileVisible(int objectX, int objectY, int objectZ, int targetX, int targetY, int targetZ)
{
    //Just spam all the possible visible spots on the target tile
    for (int z = 0; z < 24; z++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int x = 0; x < 16; x++)
            {
                if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16 + x,targetY*16+ y,targetZ*24 + z))
                {
                    return true; //If any ray hits the target, then return true
                }
            }
        }
    }
    return false; //If there is no possible way to see the tile, then return false
}

bool DDA::isTileVisibleOptimised(int objectX, int objectY, int objectZ, int targetX, int targetY, int targetZ)
{
    //The eight vertices
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+15,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+15,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+15,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+15,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
    //The centers of the top and bottom edges
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 8,targetX*16+8,targetY*16,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+8,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+8,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+15,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 8,targetX*16+8,targetY*16,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+8,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+8,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+15,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
    //centers of the side edges
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 8,targetX*16+8,targetY*16,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+8,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+15,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+8,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
    //absolute center
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+8,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
    //Center of faces
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 8,targetX*16+8,targetY*16+8,targetZ*24))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+8,targetZ*24+23))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16,targetY*16+8,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+8,targetY*16+15,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
        if(castRay(objectX*16 + 8,objectY*16 + 8,objectZ*24 + 12,targetX*16+15,targetY*16+8,targetZ*24+12))
        {
            return true; //If any ray hits the target, then return true
        }
    return false; //If there is no possible way to see the tile, then return false
}

