#include "creature.h"
#include "observer.h"
#include "subject.h"

Creature::Creature(int hp, int atk, int def, int gold): Life(), maxHp(hp), atk(atk), def(def)
                                                        , gold(gold) { 
    curHp = maxHp;
}

void Creature::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}

void Creature::attack(Life *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);
    atk -= atkModifier;
}

Creature::~Creature() { }

char Creature::getRep() { return rep; }

int Creature::getAtk() { return atk; }

int Creature::getDef() { return def; }

int Creature::getGold() { return gold; }

int Creature::getHP() { return curHp; }

int Creature::getRecentX() { return recentX; }
int Creature::getRecentY() { return recentY; }


Creature *Creature::getCreature() { return this; }

void Creature::modifyHP(int amount)  {
    curHp += amount;
    if (curHp > maxHp) {
        curHp = maxHp;
    }
}

void Creature::modifyGold(int amount) {
    gold += amount;
    if (gold < 0) {
        gold = 0;
    }
}

void Creature::setFloor(Floor *fl) {
    this->fl = fl;
}

void Creature::setStartingPosition(int posx, int posy) {
    recentX = posx;
    recentY = posy;
}