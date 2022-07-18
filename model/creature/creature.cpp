#include "creature.h"
#include "observer.h"
#include "subject.h"

Creature::Creature(int hp, int atk, int def, int gold): Subject(), hp(hp), atk(atk), def(def)
                                                        , gold(gold) { }

void Creature::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}

void  Creature::modifyHP(int amount) {
    hp += amount;
}
void Creature::modifyGold(int amount) {
    gold += amount;
}

Creature::~Creature() { }

char Creature::getRep() { return rep; }

void Creature::setFloor(Floor *fl) {
    this->fl = fl;
}

void Creature::setStartingPosition(int posx, int posy) {
    recentX = posx;
    recentY = posy;
}