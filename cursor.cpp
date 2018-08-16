#include "cursor.h"
#include "game.h"
//
Cursor::Cursor(Game* pGame)
{
    std::cout << "Creature Initialized" << std::endl;
    game = pGame; //Set the pointer to the current game

    //==================================================================
    mousePoint.setSize(sf::Vector2f(1,1));
    mousePoint.setFillColor(sf::Color::Red);
    // get the current mouse position in the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(game->renderWindow);
    // convert it to world coordinates
    sf::Vector2f worldPos = game->renderWindow.mapPixelToCoords(pixelPos);
    mousePoint.setPosition(worldPos);
    //==================================================================

}

void Cursor::refreshCursorPosition()
{
    // get the current mouse position in the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(game->renderWindow);
    // convert it to world coordinates
    sf::Vector2f worldPos = game->renderWindow.mapPixelToCoords(pixelPos);
    mousePoint.setPosition(worldPos);
}

int Cursor::getPositionX()
{
    refreshCursorPosition();
    return mousePoint.getPosition().x;
}

int Cursor::getPositionY()
{
    refreshCursorPosition();
    return mousePoint.getPosition().y;
}

