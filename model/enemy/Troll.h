//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_TROLL_H
#define CCK3_WATERLOO_S2022_PROJECT_TROLL_H
#include "Enemy.h"

class Troll: public Enemy {
    public:
        Troll();
        void move(int atkMod) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_TROLL_H
