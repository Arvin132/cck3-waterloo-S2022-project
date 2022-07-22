//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
#define CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
#include "Enemy.h"

class Dragon: public Enemy {
    public:
        Dragon();
        void move() override;
        void beAttackedBy(Creature *who, int defModifier) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_DRAGON_H
