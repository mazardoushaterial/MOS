#include "actionStates.h"
#include "testState1.h"

ActionStates::ActionStates()
{
}

ActionStates::ActionStates(TestState1 * pState)
{
  state = pState;
}
//Vtable
void ActionStates::draw(){};
void ActionStates::input(){};
void ActionStates::update(){};
