#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED
#include "creature.h"
class Game;
class Cursor
{
    public:
        Cursor(Game* pGame);
        //The mouse position (needs to be corrected, else off by pixel due to sf::view)
        sf::RectangleShape mousePoint;
        int getPositionX();
        int getPositionY();
        //What tile is the cursor on?
        int getTileX();
        int getTileY();
        int getTileZ();
    private:
        void refreshCursorPosition();
        Game * game;
        int x;
        int y;
};

#endif // CURSOR_H_INCLUDED
