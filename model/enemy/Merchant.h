//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
#define CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
#include "Enemy.h"

class Merchant : public Enemy {
    bool static isAgro;
    public:
        Merchant();
        void move() override;
        void beAttackedBy(Creature *who, int defModifier) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
