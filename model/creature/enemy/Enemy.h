//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#define CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#include "creature.h"

class Enemy: public Creature {
    public:
      void virtual attack(Creature *other, int atkModifier);
      void virtual beAttackedBy(Creature *who, int defModifier);
      void virtual move();
      void virtual modifyHP(int amount);
      void virtual modifyGold(int amount);
};


#endif //CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
