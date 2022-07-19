#ifndef __CREATURE_H_
#define __CREATURE_H_
#include "subject.h"
class Floor;

enum Direction {N=0, E, S, W};

class Creature: public Subject {
    private:
      void setFloor(Floor *fl);
      void setStartingPosition(int posx, int posy);
    protected:
      Creature(int hp, int atk, int def, int gold);
      int hp;
      int atk;
      int def;
      int gold;
      Floor *fl;
      char rep;
      
      void virtual modifyHP(int amount);
      void virtual modifyGold(int amount);

    public:
      virtual ~Creature();
      void virtual notifyObservesrs() override;
      char virtual getRep();
      int virtual getAtk();
      void virtual modifyHP(int amount);
      void virtual modifyGold(int amount);
      void virtual attack(Creature *other, int atkModifier) = 0;
      void virtual beAttackedBy(Creature *who, int defModifier) = 0;
      void virtual move() = 0;
      friend class Floor;
};

#endif