#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED
#include "creature.h"
#include <string>
#include <fstream>

class Npc: public Creature
{
    public:
        Npc();
        Npc(Game * pGame);
        void loadNpc(std::string file);
        bool withoutWeapon();
};

#endif // NPC_H_INCLUDED
