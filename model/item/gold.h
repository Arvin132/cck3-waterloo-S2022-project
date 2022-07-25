#ifndef __GOLD_H__
#define __GOLD_H__
#include "item.h"
class Creature;



class Gold: public PickUpable {
    int amount;
    public:
        Gold(int amount);
        int effect(Life *who) override;
};

#endif