//#define _GLIBCXX_USE_CXX11_ABI 0
#include "resourceManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
ResourceManager::ResourceManager()
{
    loadTextures();
}

void ResourceManager::loadTextures()
{
    //
    if (!tileTextures.loadFromFile("MOSTiles.png"))
    {
        std::cout << "MOSTiles.png did not load" << std::endl;
    }
    if (!characterTextures.loadFromFile("characters.png"))
    {
        std::cout << "character.png did not load" << std::endl;
    }
    if (!cursorTextures.loadFromFile("cursor.png"))
    {
        std::cout << "cursor.png did not load" << std::endl;
    }
    if (!projectileTextures.loadFromFile("projectile.png"))
    {
        std::cout << "projectile.png did not load" << std::endl;
    }
}
