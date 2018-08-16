#ifndef ACTIONSTATES_H_INCLUDED
#define ACTIONSTATES_H_INCLUDED
class TestState1;
class ActionStates
{
    public:
        ActionStates(); //This needs to be here for inheritance/constructor reasons
        ActionStates(TestState1 * pState);
        virtual void input();
        virtual void draw();
        virtual void update();
    protected:
        TestState1 * state;
};

#endif // ACTIONSTATES_H_INCLUDED
