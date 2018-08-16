#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
class Game; //Forward declaration
class State
{
    public:
        State(); //Need this for technical reasons (else I get an error because of inheritance)
        void logic();
        virtual void draw();
        virtual void input();
        virtual void update();
    protected:
        int tAcc;
        sf::Clock clock;
        sf::Time elapsed;
        Game* game;
};


#endif // STATE_H_INCLUDED
