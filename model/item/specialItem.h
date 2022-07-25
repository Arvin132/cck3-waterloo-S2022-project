#ifndef __SPECIAL_ITEM_H__
#define __SPECIAL_ITEM_H__
#include "item.h"
#include "potion.h"
#include "gold.h"
class Life;
class Dragon;

class DragonHoard: public Gold {
    public:
        DragonHoard();
        friend class Dragon;
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