#ifndef __CREATURE_H_
#define __CREATURE_H_
#include "Subject.h"
class Floor;

enum Direction {N=0, E, S, W, NE, NW, SE, SW, Nothing};

class Creature: public Subject {
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
      void virtual notifyObservesrs() override;
      char virtual getRep();
      int virtual getAtk();
      void virtual attack(Creature *other, int atkModifier) = 0;
      int virtual beAttackedBy(Creature *who, int defModifier) = 0;
      void virtual modifyHP(int amount) = 0;
      void virtual modifyGold(int amount) = 0;
      void virtual move() = 0;
      friend class Floor;
};

#endif