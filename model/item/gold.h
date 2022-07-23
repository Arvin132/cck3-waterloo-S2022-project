#ifndef __GOLD_H__
#define __GOLD_H__
#include "item.h"
class Creature;

class Gold: public Item {
    int amount;
    public:
        Gold(int amount);
        void effect(Life *who) override;
};

#endif