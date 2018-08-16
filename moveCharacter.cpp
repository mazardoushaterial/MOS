#include "moveCharacter.h"

MoveCharacter::MoveCharacter(TestState1 *pState)
{
    state = pState;
}


void MoveCharacter::input()
{
    sf::Event event;
    while (state->game->renderWindow.pollEvent(event))
    {
       // "close requested" event: we close the window
        switch (event.type)
        {
            case sf::Event::Closed:
                state->game->renderWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                //Select location to move
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    //Moving the player Character
                    for (int z = 0; z <= state->map.getCurrentHeight(); z++)
                    {
                        for (int y = 0; y < MAX_Y; y++)
                        {
                            for (int x = 0; x < MAX_X; x++)
                            {
                                if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > state->game->cursor.getPositionX()
                               && (x-y)*(floorWidth/2) - floorWidth/2-2 < state->game->cursor.getPositionX()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> state->game->cursor.getPositionY()
                               && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< state->game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                               && state->map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                                {
                                    if ((state->map.walkMap[z][y][x] == 0 || state->map.walkMap[z][y][x] == 2)) //Make sure we can actually go here
                                    {
                                        //configure pathfinding map
                                        state->map.configureWalkMap();
                                        //Make the player move
                                        state->testPlayer.goHere(x,y,state->map.getCurrentHeight(),state->map.walkMap);
                                        //Shoot rays
                                        state->map.drawOctants(state->testPlayer.x,state->testPlayer.y,state->testPlayer.z,state->testPlayer.facing);
                                    }

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
                state->map.increaseHeight();
            }
        }
        else if ((event.key.code == sf::Keyboard::Down))
        {
            if (event.KeyReleased == event.type)
            {
                state->map.decreaseHeight();
            }
        }
        //look around
        else if ((event.key.code == sf::Keyboard::L))
        {
            //if (event.KeyReleased == event.type)
            {

                for (int z = 0; z <= state->map.getCurrentHeight(); z++)
                {
                    for (int y = 0; y < MAX_Y; y++)
                    {
                        for (int x = 0; x < MAX_X; x++)
                        {
                            if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > state->game->cursor.getPositionX()
                           && (x-y)*(floorWidth/2) - floorWidth/2-2 < state->game->cursor.getPositionX()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> state->game->cursor.getPositionY()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< state->game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                           && state->map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the current ceiling height.
                            {
                                state->map.drawOctants(state->testPlayer.x,state->testPlayer.y,state->testPlayer.z,state->testPlayer.facing);
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
        state->map.view.move(0,-20);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        state->map.view.move(0,20);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        state->map.view.move(-20,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        state->map.view.move(20,0);
    }
    state->game->renderWindow.setView(state->map.view);


}

void MoveCharacter::update()
{

}

void MoveCharacter::draw()
{
    //map.draw(); //DELETE LATER
    for (int z = 0; z <= state->map.getCurrentHeight(); z++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
                    //Check whether the tiles are in the screen. If they are, then draw them.
                if  (
                    ((x-y)*(floorWidth/2) < state->map.view.getCenter().x + 1024 / 2 + 80)
                    &&((x-y)*(floorWidth/2) > state->map.view.getCenter().x - 1024 / 2 -80)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) < state->map.view.getCenter().y + (768 / 2)+100)
                    &&(((x+y)*(floorHeight/2)) - (z*floorToFloor) > state->map.view.getCenter().y - (768 / 2)-120)
                    )
                   {
                       //Draw cursor if on a tile.
                       if ( (x-y)*(floorWidth/2) + floorWidth/2-2 > state->game->cursor.getPositionX()
                           && (x-y)*(floorWidth/2) - floorWidth/2-2 < state->game->cursor.getPositionX()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  + 10> state->game->cursor.getPositionY()
                           && ((x+y)*(floorHeight/2)) - (z*floorToFloor)  - 10< state->game->cursor.getPositionY() //Shift up the z level -(z*ftf)
                           && state->map.getCurrentHeight() == z ) //Make sure the cursor is displayed on the curren ceiling height.
                        {
                            //Set the sprite to "cursor" when the sprite is hovered over.
                            for (int i = 0; i <= state->map.getCurrentHeight();i++) //Draw the cursor tiles underneath the main cursor tile
                            {
                                if (state->map.visible[z][y][x])
                                    state->map.drawFloor(x,y,z); //draw floor
                                //game->renderWindow.draw(map.stamper);
                                //Draw the back cursor thing
                                if (state->map.tile[i][y][x].name == "air" || i == state->map.getCurrentHeight()) //draw if there's not tile, or it's the main cursor tile
                                {
                                state->map.stamper.setTextureRect(sf::IntRect(0,tileHeight,tileWidth,tileHeight));
                                state->map.stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (i*floorToFloor));
                                state->game->renderWindow.draw(state->map.stamper);
                                if (state->map.visible[z][y][x])
                                    //draw tile
                                    state->map.drawTile(x,y,z);
                                //game->renderWindow.draw(map.stamper);
                                //draw the front cursor thing
                                state->map.stamper.setTextureRect(sf::IntRect(0,0,tileWidth,tileHeight));
                                state->map.stamper.setPosition((x-y)*(floorWidth/2),((x+y)*(floorHeight/2)) - (i*floorToFloor));
                                state->game->renderWindow.draw(state->map.stamper);
                                }
                            }
                        }
                        //Draw the actual tiles if it's visible
                        else
                        {
                            state->map.drawFloor(x,y,z);
                            state->map.drawTile(x,y,z);
                        }


                   }

                   //////////////////////////
                   //////////////////////////
                   //drawing the characters//
                   //////////////////////////
                   //////////////////////////
                   if (x == state->testPlayer.x && y == state->testPlayer.y && z == state->testPlayer.z)
                   {
                       state->testPlayer.draw();
                   }

            }
        }
    }
}
