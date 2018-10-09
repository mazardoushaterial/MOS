#include "testState1.h"
#include <iostream>
#include <math.h>
#define PI 3.14159

TestState1::TestState1(Game* pGame):
    map(pGame),
    testPlayer(pGame),
    projectile(pGame->resourceManager.projectileTextures)
{
    //weapon.loadWeapon("TESTRIFLE.wep");
    game = pGame;
    npc[0].setCharacter(pGame);
    npc[0].loadCreature("TESTDUMMY.actor");
    //changeActionState(new MoveCharacter(this));
    std::string tileInfo[4][60][60];
    std::cout << "Sorry for the wait. The voxel map is loading!" << std::endl;
    for (int z = 0; z < 4; z++)
    {
        for (int y = 0; y < 60; y++)
        {
            for (int x = 0; x < 60; x++)
            {
                tileInfo[z][y][x] = map.tile[z][y][x].name;
            }
        }
    }
    map.raycaster.setUpVoxelMap(tileInfo);
     std::cout << "Done loading!" << std::endl;
    std::cout << "voxelMapSetUp" << std::endl;

}

//You should put the difference between the start points and end points here
int TestState1::lookHere(double x, double y)
{
  double result;
  result = atan2 (y,x);
  //Convert to positive radian.
  if (result < 0)
  {
      result = 2*PI + result;
  }
  printf ("The arc tangent for (x=%f, y=%f) is %f radians\n", x, y, result );

  if (result >= (11*PI)/8 && result <= (13*PI)/8 )
  {
      return 1;
  }
  else if (result >= (13*PI)/8 && result <= (15*PI)/8 )
  {
      return 2;
  }
  else if (result >= (15*PI)/8 && result <= (16*PI)/8 || result >= 0 && result <= (PI)/8 )
  {
      return 3;
  }
  else if (result >= (PI)/8 && result <= (3*PI)/8 )
  {
      return 4;
  }
  else if (result >= (3*PI)/8 && result <= (5*PI)/8 )
  {
      return 5;
  }
  else if (result >= (5*PI)/8 && result <= (7*PI)/8 )
  {
      return 6;
  }
  else if (result >= (7*PI)/8 && result <= (9*PI)/8 )
  {
      return 7;
  }
  else if (result >= (9*PI)/8 && result <= (11*PI)/8 )
  {
      return 0;
  }
  else
  {
      std::cout << "DAMN" << std::endl;
  }
  return 0;
}

void TestState1::playerInput()
{
    sf::Event event;
    while (game->renderWindow.pollEvent(event))
    {
       // "close requested" event: we close the window
        switch (event.type)
        {
            case sf::Event::Closed:
                game->renderWindow.close();
                break;
            case sf::Event::MouseButtonReleased:
                //Select location to move
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    //Moving the player Character
                    for (int z = 0; z <= map.getCurrentHeight(); z++)
                    {
                        for (int y = 0; y < MAX_Y; y++)
                        {
                            for (int x = 0; x < MAX_X; x++)
                            {
                                if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                               && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                               && map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                                {
                                    if ((map.walkMap[z][y][x] == 0 || map.walkMap[z][y][x] == 2)) //Make sure we can actually go here
                                    {
                                        //configure pathfinding map
                                        map.configureWalkMap();
                                        //Make the player move
                                        testPlayer.goHere(x,y,map.getCurrentHeight(),map.walkMap);
                                        //Shoot rays
                                        map.drawOctants(testPlayer.x,testPlayer.y,testPlayer.z,testPlayer.getFacing());
                                    }

                                }
                            }
                        }
                    }

                }
                 //Select location to look
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    //Moving the player Character
                    for (int z = 0; z <= map.getCurrentHeight(); z++)
                    {
                        for (int y = 0; y < MAX_Y; y++)
                        {
                            for (int x = 0; x < MAX_X; x++)
                            {
                                if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                               && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                               && map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                                {
                                    testPlayer.changeFacing(lookHere((testPlayer.getPositionX()-x),(testPlayer.getPositionY()-y)));
                                    map.drawOctants(testPlayer.x,testPlayer.y,testPlayer.z,testPlayer.getFacing());
                                }
                            }
                        }
                    }

                }

                break;

            case sf::Event::KeyReleased:

                if (event.key.code == sf::Keyboard::F)
                {
                    for (int z = 0; z <= map.getCurrentHeight(); z++)
                        {
                            for (int y = 0; y < MAX_Y; y++)
                            {
                                for (int x = 0; x < MAX_X; x++)
                                {
                                    if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                                   && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                                   && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                                   && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                                   && map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                                    {
                                        testPlayer.changeFacing(lookHere((testPlayer.getPositionX()-x),(testPlayer.getPositionY()-y)));
                                        map.drawOctants(testPlayer.x,testPlayer.y,testPlayer.z,testPlayer.getFacing());
                                        projectile.setWeapon(testPlayer.weapon);
                                        projectile.shoot(testPlayer.x,testPlayer.y,testPlayer.z,x,y,z);
                                    }
                                }
                            }
                        }
                }

                break;
        }


        if ((event.key.code == sf::Keyboard::Up))
        {
            if (event.KeyReleased == event.type)
            {
                map.increaseHeight();
            }
        }
        else if ((event.key.code == sf::Keyboard::Down))
        {
            if (event.KeyReleased == event.type)
            {
                map.decreaseHeight();
            }
        }
        //look around
        else if ((event.key.code == sf::Keyboard::L))
        {
            //if (event.KeyReleased == event.type)
            {

                for (int z = 0; z <= map.getCurrentHeight(); z++)
                {
                    for (int y = 0; y < MAX_Y; y++)
                    {
                        for (int x = 0; x < MAX_X; x++)
                        {
                            if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                           && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                           && map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                            {
                                map.drawOctants(testPlayer.x,testPlayer.y,testPlayer.z,testPlayer.getFacing());
                            }
                        }
                    }
                }
            }
        }
    }

    //real time input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        map.view.move(0,-20);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        map.view.move(0,20);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        map.view.move(-20,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        map.view.move(20,0);
    }
    game->renderWindow.setView(map.view);

}

void TestState1::input()
{
    playerInput();
}


/*
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
        //putTile(round(x),round(y),round(z));
    }
*/


void TestState1::update()
{
    updateProjectile();
}

void TestState1::updateProjectile()
{
    //For the sake of speed, let's update 5 times per frame
    for (int i = 0; i < 5; i++)
    {
        projectile.update();
        projectileCheck(); //collisions with actors
        if (map.raycaster.voxelMap[projectile.getRoundPositionZ()][projectile.getRoundPositionY()][projectile.getRoundPositionX()])
        {
            projectile.stopMoving();
        }
    }
}

void TestState1::draw()
{
    drawBattleScape();
    drawProjectile();
}


void TestState1::drawBattleScape()
{
    //map.draw(); //DELETE LATER
    for (int z = 0; z <= map.getCurrentHeight(); z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                    //Check whether the tiles are in the screen. If they are, then draw them.
                if  (
                    ((x-y)*(floorWidth/2) < map.view.getCenter().x + 1024 / 2 + 80)
                    &&((x-y)*(floorWidth/2) > map.view.getCenter().x - 1024 / 2 -80)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) < map.view.getCenter().y + (768 / 2)+100)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) > map.view.getCenter().y - (768 / 2)-120)
                    )
                   {
                       //Draw cursor if on a tile.
                       if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > game->cursor.getPositionX()
                           && (x-y)*(floorWidth/2) - floorWidth/2-2 < game->cursor.getPositionX()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> game->cursor.getPositionY()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                           && map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the curren ceiling height.
                        {
                            //Set the sprite to "cursor" when the sprite is hovered over.
                            for (int i = 0; i <= map.getCurrentHeight();i++) //Draw the cursor tiles underneath the main cursor tile
                            {
                                if (map.visible[z][y][x])
                                    map.drawFloor(x,y,z); //draw floor
                                //game->renderWindow.draw(map.stamper);
                                //Draw the back cursor thing
                                if (map.tile[i][y][x].name == "air" || i == map.getCurrentHeight()) //draw if there's not tile, or it's the main cursor tile
                                {
                                map.stamper.setTextureRect(sf::IntRect(0,tileHeight,tileWidth,tileHeight));
                                map.stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (i*floorToFloor));
                                game->renderWindow.draw(map.stamper);
                                if (map.visible[z][y][x])
                                    //draw tile
                                    map.drawTile(x,y,z);
                                //game->renderWindow.draw(map.stamper);
                                //draw the front cursor thing
                                map.stamper.setTextureRect(sf::IntRect(0,0,tileWidth,tileHeight));
                                map.stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (i*floorToFloor));
                                game->renderWindow.draw(map.stamper);
                                }
                            }
                        }
                        //Draw the actual tiles if it's visible
                        else
                        {
                            map.drawFloor(x,y,z);
                            map.drawTile(x,y,z);
                        }


                   }

                   //////////////////////////
                   //////////////////////////
                   //drawing the characters//
                   //////////////////////////
                   //////////////////////////
                   if (x == testPlayer.x && y == testPlayer.y && z == testPlayer.z)
                   {
                       testPlayer.draw();
                   }

                   if (x == npc[0].x && y == npc[0].y && z == npc[0].z)
                   {
                       npc[0].draw();
                   }

            }
        }
    }
}

void TestState1::drawProjectile()
{
    projectile.draw(game->renderWindow);
}

void TestState1::projectileCheck()
{
    //If a collision occurs with the NPC
    int i = 0;
    if (
        projectile.getRoundPositionY() > npc[i].getCollisionNorth() &&
        projectile.getRoundPositionY() < npc[i].getCollisionSouth() &&
        projectile.getRoundPositionX() < npc[i].getCollisionEast() &&
        projectile.getRoundPositionX() > npc[i].getCollisionWest() &&
        projectile.getRoundPositionZ() < npc[i].getCollisionUp()   &&
        projectile.getRoundPositionZ() > npc[i].getCollisionDown()
        )
    {
        std::cout << "OW! I'm hit!" << std::endl;
    }
}

void TestState1::changeActionState(ActionStates * pAction)
{
    //action = pAction;
}
