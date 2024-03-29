//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
#define CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
#include "Enemy.h"

class Merchant : public Enemy {
    static bool isAgro;
    public:
        Merchant();
        ~Merchant();
        void move(int atkMod) override;
        int beAttackedBy(Life *who, int defModifier) override;
        std::string getInfo() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_MERCHANT_H
