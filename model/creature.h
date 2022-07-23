#ifndef __CREATURE_H_
#define __CREATURE_H_
#include "life.h"
#include <string>

class Floor;

enum Direction {N=0, E, S, W, NE, NW, SE, SW, Nothing};

class Creature: public Life {
    private:
      void setFloor(Floor *fl);
      void setStartingPosition(int posx, int posy);
    protected:
      Creature(int hp, int atk, int def, int gold);
      int maxHp, atk, def, gold;
      Floor *fl;
      char rep;
      int curHp;

    public:
      virtual ~Creature();
      void notifyObservesrs() override;
      char getRep() override;
      int getAtk() override;
      int getDef() override;
      int getGold() override;
      int getHP() override;
      std::string virtual report() = 0;
      void virtual modifyHP(int amount) override;
      void virtual modifyGold(int amount) override;
      int getRecentX() override;
      int getRecentY() override;
      Creature *getCreature() override;
      void virtual attack(Life *other, int atkModifier);
      friend class Floor;
};

#endif