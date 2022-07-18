//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#define CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#include "creature.h"

class Enemy: public Creature {
    public:
      ~Enemy();
      void virtual attack(Creature *other, int atkModifier);
      void virtual beAttackedBy(Creature *who, int defModifier);
      virtual void move();
};


#endif //CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
