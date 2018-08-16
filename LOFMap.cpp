#include "LOFMap.h"

LOFMap::LOFMap()
{
    loadLOFMaps();
}

void LOFMap::setUpVoxelMap(std::string tileBoard[4][60][60])
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
                                voxelMap[z*24 + vz][y*16 + vy][x*16 + vx] = full[vz][vy][vx];
                            }
                        }
                    }
                }
        }
    }
    }
}

void LOFMap::loadLOFMaps()
{
    std::ifstream getMap;
    //TEST
    getMap.open("test.LOF");
    for (int z = 0; z < LOF_Z; z++)
    {
        for (int y = 0; y < LOF_Y; y++)
        {
            for (int x = 0; x < LOF_X; x++)
            {
            getMap >> test[z][y][x];
            }
        }
    }
    getMap.close();
    //str_concrete7
    getMap.open("str_concrete5.LOF");
    for (int z = 0; z < LOF_Z; z++)
    {
        for (int y = 0; y < LOF_Y; y++)
        {
            for (int x = 0; x < LOF_X; x++)
            {
            getMap >> str_concrete5[z][y][x];
            //std::cout << str_concrete5[z][y][x];
            }
        //std::cout << std::endl;
        }
    //std::cout << std::endl;
    }
    getMap.close();
    //Full of blocks
    for (int z = 0; z < LOF_Z; z++)
    {
        for (int y = 0; y < LOF_Y; y++)
        {
            for (int x = 0; x < LOF_X; x++)
            {
            full[z][y][x] = true;
            }
        }
    }
    /*
    for (int z = 0; z < LOF_Z; z++)
    {
        for (int y = 0; y < LOF_Y; y++)
        {
            for (int x = 0; x < LOF_X; x++)
            {
                std::cout << str_concrete7[z][y][x];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    */


}
