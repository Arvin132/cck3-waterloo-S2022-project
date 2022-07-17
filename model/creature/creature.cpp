#include "creature.h"
#include "subject.h"

Creature::Creature(int hp, int atk, int def, int gold): hp(hp), atk(atk), def(def)
                                                        , gold(gold) { }

Creature::~Creature() { }

char Creature::getRep() { return rep; }

void Creature::setFloor(Floor *fl) {
    this->fl = fl;
}

void Creature::setStartingPosition(int posx, int posy) {
    recentX = posx;
    recentY = posy;
}