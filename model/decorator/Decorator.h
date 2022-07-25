//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H
#define CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H

#include "life.h"
#include <memory>
#include "creature.h"


class Decorator: public Life {
    
    protected:
      Decorator(Life *next);
      Life *next;
    public:
      virtual ~Decorator();
      void beEffectedBy(Item *what) override;
      void notifyObservesrs() override;
      void modifyHP(int amount) override;
      void modifyGold(int amount) override;
      char getRep() override;
      int getGold() override;
      int getHP() override;
      int getRecentX() override;
      int getRecentY() override;
      void addBarrierSuite() override;
      Creature *getCreature() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_DECORATOR_H
