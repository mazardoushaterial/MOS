#include "map.h"
#include "game.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

Map::Map(Game* pGame):
    view(sf::FloatRect(0, 0, 1024, 768))
{
    height = 0;
    game = pGame;
    stamper.setTexture(game->resourceManager.tileTextures);
    stamper.setOrigin(44,20);
    //setUpTiles();
    //setUpFloor();
    loadMap();
    //lof.loadLOFMaps();
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int z = 0; z < MAX_Z; z++)
            {
                visible[z][y][x] = false;
            }
        }
    }
}

int Map::getCurrentHeight()
{
    return height;
}

bool Map::outOfBounds(int x, int y, int z)
{
    //If any of these conditions are met, then we fail
    return (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y || z < 0 || z >= MAX_Z); //current element compared to map size
}

void Map::loadMap()
{
    std::ifstream getMap;
    //Load map
    //getMap.open("forestMaze.MOS");
    getMap.open("test1.MOS");
    for (int z = 0; z < MAX_Z; z++)
    {

        for (int tof = 0; tof < 2; tof++) //tile or floor? 0=floor, 1 = tile
        {
            for (int y = 0; y < MAX_Y; y++)
            {
                for (int x = 0; x < MAX_X; x++)
                {
                    //We have to share the 'z' variable for floors and tiles
                    if(tof == 0) //even = floor
                    {
                        getMap >> floor[z][y][x].name;
                    }
                    else //odd = tile
                    {
                        getMap >> tile[z][y][x].name;
                    }
                }
            }
        }
    }
    getMap.close();

}

void Map::increaseHeight()
{
    if (height < MAX_Z-1)
    {
        height++;
    }
}

void Map::decreaseHeight()
{
    if (height != 0)
    {
        height--;
    }
}

void Map::drawTile(int x, int y, int z)
{
    //Set the tile as visible or invisible
    if(!visible[z][y][x])
    {
        stamper.setColor(sf::Color::Black);
    }
    else
    {
        stamper.setColor(sf::Color(255,255,255));
    }


    if (tile[z][y][x].name == "wall")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*2,tileHeight*3,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete5")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*0,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete3")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*1,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete7")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*2,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete1")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*3,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete6")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*4,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete2")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*5,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete4")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*6,tileHeight*5,tileWidth,tileHeight));
    }
    else if (tile[z][y][x].name == "str_concrete0")
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*7,tileHeight*5,tileWidth,tileHeight));
    }
    else
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*0,tileHeight*2,0,0));
    }
    stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (z*floorToFloor));
    game->renderWindow.draw(stamper);
    stamper.setColor(sf::Color(255,255,255));//Reset the stamper colour
}

void Map::drawFloor(int x, int y, int z)
{
    //Set the tile as visible or invisible
    if(!visible[z][y][x])
    {
        stamper.setColor(sf::Color::Black);
    }
    else
    {
        stamper.setColor(sf::Color(255,255,255));
    }

    if (floor[z][y][x].name == "grass")
    {
        //(posX-posY)*(87/2),(posX+posY)*(39/2)
        stamper.setTextureRect(sf::IntRect(tileWidth*1,tileHeight*0,tileWidth,tileHeight));
    }
    else
    {
        stamper.setTextureRect(sf::IntRect(tileWidth*0,tileHeight*2,tileWidth,tileHeight));
    }
    stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (z*floorToFloor));
    game->renderWindow.draw(stamper);

    stamper.setColor(sf::Color(255,255,255));   //reset the stamper colour
}



//Temporary debug class. We'll need enemies interlaced later, so this method is useless later.
void Map::draw()
{
    for (int z = 0; z <= height; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                    //Check whether the tiles are in the screen. If they are, then draw them.
                if  (
                    ((x-y)*(floorWidth/2) < view.getCenter().x + 1024 / 2 + 80)
                    &&((x-y)*(floorWidth/2) > view.getCenter().x - 1024 / 2 -80)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) < view.getCenter().y + (768 / 2)+100)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) > view.getCenter().y - (768 / 2)-120)
                    )
                   {
                       //Draw cursor if on a tile.
                       if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                           && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                           && height == z ) //Make sure the cursor is displayed on the curren ceiling height.
                        {
                            //Set the sprite to "cursor" when the sprite is hovered over.
                            stamper.setTextureRect(sf::IntRect(0,0,tileWidth,tileHeight));
                            stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (z*floorToFloor));
                            game->renderWindow.draw(stamper);
                        }
                        //Draw the actual tiles
                       else
                       {
                        drawFloor(x,y,z);
                        drawTile(x,y,z);
                       }
                   }
            }
        }
    }
}

void Map::setUpTiles()
{
    for (int z = 0; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                //Odds and evens, checkerboard
                if (z == 0)
                {
                    tile[z][y][x].name = "wall";
                    tile[z][y][x].health = 1;
                }
                else
                {
                    tile[z][y][x].name = "air";
                    tile[z][y][x].health = 1;
                }
            }
        }
    }
}

void Map::setUpFloor()
{
    for (int z = 0; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                floor[z][y][x].name = "grass";
                floor[z][y][x].health = 1;
            }
        }
    }
}


void Map::configureWalkMap()
{
    for (int z = 0; z < MAX_Z; z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                //Warning: Could cause out of bounds error, if the at() function goes out of bounds
                //Fix: Never make a string size less than 3 characters
                if((tile[z][y][x].name.at(0) == 's') && (tile[z][y][x].name.at(1) == 't') && (tile[z][y][x].name.at(2) == 'r')) //stairs
                {
                    walkMap[z][y][x] = 2; //stairs
                }
                else if (tile[z][y][x].name == "air" && floor[z][y][x].name != "air") //The tile contains nothing and the floor is something
                {
                    walkMap[z][y][x] = 0; //walkable
                }
                //Being on top of the stairs-
                else if (tile[z][y][x].name == "air" && floor[z][y][x].name == "air")
                {
                    if ((tile[z-1][y][x].name.at(0) == 's') && (tile[z-1][y][x].name.at(1) == 't') && (tile[z-1][y][x].name.at(2) == 'r') && (!outOfBounds(x,y,z-1)))
                    {
                        walkMap[z][y][x] = 0;
                    }
                    else //Keep this here because not setting the walkMap defaults it to the value zero
                    {
                        walkMap[z][y][x] = 1;
                    }
                }
                else //otherwise it is blocked
                {
                    walkMap[z][y][x] = 1;
                }
            }
        }
    }
    /*
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            std::cout << walkMap[0][y][x]; //stairs
        }
        std::cout << std::endl;
    }
    */


}


//DDA STUFF HERE

bool Map::tileOutOfBounds(int x, int y, int z)
{
    //If any of these conditions are met, then we fail
    return (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y || z < 0 || z >= MAX_Z); //current element compared to map size
}


void Map::drawOctant(int playerW, int playerS, int playerZ, int octant)
{
    int sInc, wInc; //step and walk; a.k.a master and slave
    switch(octant)
    {
        case 0:
            sInc = -1;
            wInc = 1;
            break;
        case 1:
            sInc = 1;
            wInc = -1;
            break;
        case 2:
            sInc = 1;
            wInc = 1;
            break;
        case 3:
            sInc = 1;
            wInc = 1;
            break;
        case 4:
            sInc = 1;
            wInc = -1;
            break;
        case 5:
            sInc = -1;
            wInc = 1;
            break;
        case 6:
            sInc = -1;
            wInc = -1;
            break;
        case 7:
            sInc = -1;
            wInc = -1;
            break;
    }
    int w = playerW,s = playerS;
    //Make a projection of the basic octant with modifiers from above
    for (int z = 0; z < 4; z++)
    {
        for (int step = 0; step < 20; step++) //less than MAX_X because MAX_X and MAX_Y are the same
        {
            for (int walk = 0; walk <= step; walk++) //Do the slave
            {
                if(octant == 3 || octant == 4 ||octant == 0 ||octant == 7) //For when y is dominant
                {
                    w = playerW + walk*wInc; //increase or decrease by factor of wInc to get new projected co-ord
                    s = playerS + step*sInc; //increase or decrease by factor of sInc
                    //draw(w,s); //y = step
                }
                else
                {
                    w = playerW + step*sInc; //increase or decrease by factor of wInc to get new projected co-ord
                    s = playerS + walk*wInc; //increase or decrease by factor of sInc
                    //draw(w,s); //y = step
                }
                //Actually cast a ray
                if (!tileOutOfBounds(w,s,z))
                {
                    if(raycaster.isTileVisibleOptimised(playerW,playerS,playerZ,w,s,z))
                    {
                        setVisible(w,s,z);
                    }
                }
            }
        }
    }
}


void Map::setVisible(int x, int y, int z)
{
    visible[z][y][x] = true;
}

void Map::drawOctants(int x, int y, int z, int facing)
{
    int o1, o2; //octant 1 and 2 parameter
    switch(facing)
    {
    case 0:
        o1 = 6;//
        o2 = 7;
        break;
    case 1:
        o1 = 7;
        o2 = 0;
        break;
    case 2:
        o1 = 0;
        o2 = 1; //
        break;
    case 3:
        o1 = 1;//
        o2 = 2;//
        break;
    case 4:
        o1 = 2;//
        o2 = 3;
        break;
    case 5:
        o1 = 3;
        o2 = 4;
        break;
    case 6:
        o1 = 4;
        o2 = 5;//
        break;
    case 7:
        o1 = 5;//
        o2 = 6;//
        break;
    }
    drawOctant(x,y,z,o1);
    drawOctant(x,y,z,o2);
}



