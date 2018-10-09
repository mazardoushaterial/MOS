#ifndef AMMUNITION_H_INCLUDED
#define AMMUNITION_H_INCLUDED
#include <string>

//Bullet modifier
#define NONE 0
#define BALLISTIC 1
#define FIRE 2
#define LASER 3
#define STUN 4
#define EXPLOSIVE 5

class Ammunition
{
    /*
    public:
        std::string getName();
        int getAmount();
        int getDamage();
        int getModifier();
        std::string getType();

        void setAmount(int i);
        void setDamage(int i);
        void setModifier(int i);
        void setType(int i);
        */
    public:
        std::string name;
        int amount;
        int damage; //bonus damage for the weapon type
        int modifier;
        std::string type;
};

#endif // AMMUNITION_H_INCLUDED
