//#define _GLIBCXX_USE_CXX11_ABI 0
#include "game.h"
Game::Game():
    WINDOW_WIDTH(1024),
    WINDOW_HEIGHT(768),
    cursor(this)
    //mapHandler(this)
{
    changeState(new TestState1(this));
    renderWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"MOS: Foreign Enemy Taskforce");
    //renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);
}

void Game::changeState(State* nState)
{
    state = nState;
}

void Game::mainGameLoop()
{
    // The main loop - ends as soon as the window is closed
    while (renderWindow.isOpen())
    {
       //
       // Clear the whole window before rendering a new frame
       renderWindow.clear();


       state->logic();
       //renderWindow.draw(sFade);

       // End the current frame and display its contents on screen
       renderWindow.display();
    }
}
