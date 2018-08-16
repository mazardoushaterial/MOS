#ifndef COLLISIONMAP_H_INCLUDED
#define COLLISIONMAP_H_INCLUDED
#define MAX_X 540 //9 voxels wide, 60 tiles
#define MAX_Y 540 //9 voxels wide, 60 tiles
#define MAX_Z 180 //20 voxels tall, 4 tiles
//============================
//Voxel collision map
//============================
class CollisionMap
{
    public:
        char map[MAX_Z][MAX_Y][MAX_X];
    private:
        void resetMap(); //Turn all bytes to 0x00
};


#endif // COLLISIONMAP_H_INCLUDED
