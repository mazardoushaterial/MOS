#ifndef LOFMAP_H_INCLUDED
#define LOFMAP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>

//Maximum size of the line of fire maps
#define LOF_X 16
#define LOF_Y 16
#define LOF_Z 24
#define VOX_X 60*LOF_X
#define VOX_Y 60*LOF_Y
#define VOX_Z 4*LOF_Z

class LOFMap
{
    public:

        LOFMap();

        void setUpVoxelMap(std::string tileBoard[4][60][60]);

        bool voxelMap[VOX_Z][VOX_Y][VOX_X];

        bool full[LOF_Z][LOF_Y][LOF_X];
        bool test[LOF_Z][LOF_Y][LOF_X];
        bool blank[LOF_Z][LOF_Y][LOF_X];
        bool str_concrete5[LOF_Z][LOF_Y][LOF_X];
        bool str_concrete3[LOF_Z][LOF_Y][LOF_X];

        void loadLOFMaps();
};



#endif // LOFMAP_H_INCLUDED
