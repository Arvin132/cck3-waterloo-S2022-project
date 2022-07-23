//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#define CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
#include "../creature.h"

Direction directionOfCommand(int d, int *newX, int *newY);

class Enemy: public Creature {
    
    protected:
      Enemy(int hp, int atk, int def);
    public:
      virtual ~Enemy();
      int virtual beAttackedBy(Life *who, int defModifier) override;
      void beEffectedBy(Item  *what) override;
      virtual void move(int atkMod);
      std::string report() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_ENEMY_H
