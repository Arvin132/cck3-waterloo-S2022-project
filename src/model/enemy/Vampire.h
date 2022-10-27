//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_VAMPIRE_H
#define CCK3_WATERLOO_S2022_PROJECT_VAMPIRE_H
#include "Enemy.h"

class Vampire: public Enemy {
    public:
        Vampire();
        ~Vampire();
        void attack(Life *other, int atkModifier) override;
        std::string getInfo() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_VAMPIRE_H
