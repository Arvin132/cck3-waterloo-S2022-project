#ifndef __SPECIAL_ITEM_H__
#define __SPECIAL_ITEM_H__
#include "item.h"
#include "potion.h"
class Life;

class DragonHoard: public PickUpable {
    public:
        DragonHoard();
        void effect(Life *who) override;
};

class BarrierSuite: public PickUpable {
    public:
        BarrierSuite();
        void effect(Life *who) override;
};

class Compass: public PickUpable {
    public:
        Compass();
        void effect(Life *who) override;
};

class Stairs: public PickUpable {
    bool *nxtFlr;
    public:
        Stairs();
        void effect(Life *who) override;

};


#endif