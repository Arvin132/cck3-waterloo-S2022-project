//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_GOBLIN_H
#define CCK3_WATERLOO_S2022_PROJECT_GOBLIN_H
#include "Enemy.h"

class Goblin : public Enemy {
    public:
      Goblin();
      void attack(Life *other, int atkModifier) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_GOBLIN_H
