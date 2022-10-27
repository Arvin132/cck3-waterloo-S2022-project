#ifndef __LIFE_H__
#define __LIFE_H__
#include "subject.h"
class Item;
class Creature;

class Life : public Subject {
    protected:
        Life();
    public:
        virtual ~Life();
        char virtual getRep() = 0;
        int virtual getAtk() = 0;
        int virtual getDef() = 0;
        int virtual getGold() = 0;
        int virtual getHP() = 0;
        virtual std::string getInfo() = 0;
        void virtual modifyHP(int amount) = 0;
        void virtual modifyGold(int amount) = 0;
        void virtual move(int atkMod) = 0;
        int virtual beAttackedBy(Life *who, int defModifier) = 0;
        void virtual beEffectedBy(Item *what) = 0;
        virtual Creature *getCreature() = 0;
        virtual void addBarrierSuite() = 0;
};

#endif