//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
#define CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
#include "Enemy.h"
class DragonHoard;

class Creature;

class Dragon: public Enemy {
    Item *defending;
    public:
        Dragon(Item *defending);
        ~Dragon();
        void move(int atkMod) override;
        int beAttackedBy(Life *who, int defModifier) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
