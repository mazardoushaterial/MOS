#ifndef TESTSTATE1_H_INCLUDED
#define TESTSTATE1_H_INCLUDED
#include "projectile.h"
#include "map.h"
#include "state.h"
#include "creature.h"
#include "cursor.h"
#include "game.h"
#include "actionStates.h"
#include "moveCharacter.h"
#include "weapon.h"
#include <SFML/Graphics.hpp>
class ActionStates;
class MoveCharacter;
class TestState1: public State
{
    public:

        std::string tileName[4][60][60];
        Projectile projectile;
        TestState1(Game* pGame);
        //ActionStates * action;
        void update();
        void draw();
        void input();
        void changeActionState(ActionStates * pAction);
        void drawBattleScape();
        void drawProjectile();
        int lookHere(double x, double y);
        //void shoot(int x1, int y1, int z1, int x2, int y2, int z2);
        Game * game;
        Map map;
        Creature testPlayer;
        Weapon weapon;
    protected:
        //MapHandler mapHandler;
};

#endif // TESTSTATE1_H_INCLUDED
