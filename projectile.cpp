#include "projectile.h"

Projectile::Projectile()
{
    stopMoving();
    setPosition(0,0,0);
}

Projectile::Projectile(sf::Texture pTexture)
{
    stopMoving();
    setPosition(0,0,0);
    texture = pTexture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(16,0,16,16));
}

void Projectile::setWeapon(Weapon weapon)
{
    this->sprite.setTextureRect(sf::IntRect(weapon.ammo.modifier*16,0,16,16));
}

int Projectile::getRoundPositionX()
{
    return round(x);
}

int Projectile::getRoundPositionY()
{
    return round(y);
}

int Projectile::getRoundPositionZ()
{
    return round(z);
}

float Projectile::getRawPositionX()
{
    return x;
}

float Projectile::getRawPositionY()
{
    return y;
}

float Projectile::getRawPositionZ()
{
    return z;
}

void Projectile::startMoving()
{
    moving = true;
}

void Projectile::stopMoving()
{
    moving = false;
}

bool Projectile::isMoving()
{
    return moving;
}

int Projectile::getVecX()
{
    return vecX;
}

int Projectile::getVecY()
{
    return vecY;
}

int Projectile::getVecZ()
{
    return vecZ;
}


void Projectile::setTrajectory(float x, float y, float z)
{
    this->vecX = x;
    this->vecY = y;
    this->vecZ = z;
}

void Projectile::update()
{
    if (outOfBounds() && isMoving())
    {
        std::cout << "----END----" << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << z << std::endl;
        stopMoving();
    }
    else if (!outOfBounds() && isMoving())
    {
        move();
        //std::cout << "----MOVING----" << std::endl;
        //std::cout << x << std::endl;
        //std::cout << y << std::endl;
        //std::cout << z << std::endl;
    }
}

void Projectile::move()
{
    x += vecX;
    y += vecY;
    z += vecZ;
}

bool Projectile::outOfBounds()
{
    if(round(x) >= 16*60 || round(x) <= 0)
    {
        return true;
    }
    else if (round(y) >= 16*60 || round(y) <= 0)
    {
        return true;
    }
    else if (round(z) >= 24*4 || round(z) <= 0)
    {
        return true;
    }
    return false;
}

void Projectile::shoot(int x1, int y1, int z1, int x2, int y2, int z2)
{
    //
    // /!\WARNING/!\
    // You should set up the projectile using this->setWeapon first!
    //


    if (isMoving())
        return;
    if (x1 == x2 && y1 == y2 && z1 == z2)
        return;
    double oAngle = atan2(x1-x2,y1-y2);
    std::cout << "oAngle: " << oAngle << std::endl;
    //Convert to collision coord
    x1 = x1*16+8;
    y1 = y1*16+8;
    z1 = z1*24+12;
    //Convert to collision coord
    x2 = x2*16+8;
    y2 = y2*16+8;
    z2 = z2*24+12;
    std::cout << "----START---" << std::endl;
    std::cout << x1 << std::endl;
    std::cout << y1 << std::endl;
    std::cout << z1 << std::endl;
    std::cout << "----PRESUMED END---" << std::endl;
    std::cout << x2 << std::endl;
    std::cout << y2 << std::endl;
    std::cout << z2 << std::endl;

    //Establish movement vector
    int steps;
    float dx, dy, dz, incX, incY, incZ, x = x1, y = y1, z = z1;
    dx = x2-x1;
    dy = y2-y1;
    dz = z2-z1;
    if (std::abs(dx) > std::abs(dy))
    {
        steps = std::abs(dx);
        if (std::abs(dz) > std::abs(dx))
        {
            steps = std::abs(dz);
        }
    }
    else
    {
        steps = std::abs(dy);
        if (std::abs(dz) > std::abs(dy))
        {
            steps = std::abs(dz);
        }
    }
    incX = dx / (float)steps;
    incY = dy / (float)steps;
    incZ = dz / (float)steps;

    setPosition(x1,y1,z1); //Position Vector
    setTrajectory(incX,incY,incZ); //Movement vector
    std::cout << "----DIR---" << std::endl;
    std::cout << incX << std::endl;
    std::cout << incY << std::endl;
    std::cout << incZ << std::endl;
    startMoving();
}

//The position will be in collision coords
void Projectile::setPosition(int x, int y, int z)
{
    //put it in the middle of the tile
    this->x = x;
    this->y = y;
    this->z = z;
}

void Projectile::draw(sf::RenderWindow &renderWindow)
{
    if (!isMoving())
    {
        return;
    }
    setSpriteToTilePosition();
    renderWindow.draw(sprite);
}

void Projectile::setSpritePosition(float x, float y)
{
    sprite.setPosition(x,y);
}

void Projectile::setSpriteToTilePosition()
{
    setSpritePosition(((x-y)*(floorWidth/2))/16-8,(((x+y)*(floorHeight/2))/16 - (z*(floorToFloor/24))) + floorToFloor);
    //setSpritePosition((getTileCoord(x)-getTileCoord(y))*(floorWidth/2),((getTileCoord(x)+getTileCoord(y))*(floorHeight/2)) - ((((int)z-((int)z%24))/24)*floorToFloor));
}

int Projectile::getTileCoord(float a)
{
    return ((((int)a-(int)a%16))/16); //Convert from collision Coord, to the tilemap Coord
}
