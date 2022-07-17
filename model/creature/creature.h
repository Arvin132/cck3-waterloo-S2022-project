#ifndef __CREATURE_H_
#define __CREATURE_H_
#include "subject.h"
class Floor;

enum Direction {N=0, E, S, W};

class Creature: public Subject {
    protected:
      Creature(int hp, int atk, int def, int gold);
      int hp;
      int atk;
      int def;
      int gold;
      Floor *fl;
      char rep;
    public:
      virtual ~Creature();
      void virtual attack(Creature *other, int atkModifier) = 0;
      void virtual beAttackedBy(Creature *who, int defModifier) = 0;
      void virtual move() = 0;
      void virtual modifyHP(int amount) = 0;
      void virtual modifyGold(int amount) = 0;
      char getRep();
      void setFloor(Floor *fl);
      void setStartingPosition(int posx, int posy);

};

#endif