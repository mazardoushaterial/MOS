#ifndef MOVECHARACTER_H_INCLUDED
#define MOVECHARACTER_H_INCLUDED
#include "actionStates.h"
#include "testState1.h"
//#include "game.h"
class MoveCharacter: public ActionStates
{
    public:
        MoveCharacter(TestState1 *pState);
        void draw();
        void input();
        void update();
};

#endif // MOVECHARACTER_H_INCLUDED
