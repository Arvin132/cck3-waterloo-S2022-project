//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H
#define CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H
#include "../creature.h"

class Decorator: public Creature {
    Creature *next;
    public:
      void notifyObservesrs() override;
      char getRep() override;
      void modifyHP(int amount) override;
      void modifyGold(int amount) override;
      void move() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H
