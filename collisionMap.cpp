#include "collisionMap.h"

void CollisionMap::resetMap()
{
    for (int z = 0; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                map[z][y][x] = 0x00;
            }
        }
    }
}
