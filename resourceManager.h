#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
class ResourceManager
{
    public:
        ResourceManager();
        sf::Texture tileTextures;
        sf::Texture characterTextures;
        sf::Texture cursorTextures;
        sf::Texture projectileTextures;
    private:
        void loadTextures();
};

#endif // RESOURCEMANAGER_H_INCLUDED
