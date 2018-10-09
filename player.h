#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "creature.h"

class Player: public Creature
{
    public:
        Player(Game * pGame);
};

#endif // PLAYER_H_INCLUDED
