#ifndef MAPHANDLER_H_INCLUDED
#define MAPHANDLER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Game;
class MapHandler
{
  public:
        MapHandler(Game* pGame);
  private:
        Game* game;
  public:
};

#endif // MAPHANDLER_H_INCLUDED
