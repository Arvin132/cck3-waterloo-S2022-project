#include "creature.h"
#include "Observer.h"
#include "Subject.h"

Creature::Creature(int hp, int atk, int def, int gold): Subject(), maxHp(hp), atk(atk), def(def)
                                                        , gold(gold) { 
    curHp = maxHp;
}

void Creature::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}


Creature::~Creature() { }

char Creature::getRep() { return rep; }

int Creature::getAtk() { return atk; }

void Creature::setFloor(Floor *fl) {
    this->fl = fl;
}

void Creature::setStartingPosition(int posx, int posy) {
    recentX = posx;
    recentY = posy;
}