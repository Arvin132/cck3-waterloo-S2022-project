//
// Created by kmajdi on 2022-07-14.
//

#include "Decorator.h"

Decorator::Decorator(Life *next):  next(next) {}

Decorator::~Decorator() { delete next; }

void Decorator::beEffectedBy(Item *what) { next->beEffectedBy(what); }


char Decorator::getRep() {
    return next->getRep();
}

int Decorator::getGold() { return next->getGold(); }

int Decorator::getHP() { return next->getHP(); }

void Decorator::notifyObservesrs() {
    next->notifyObservesrs();
}

void Decorator::modifyGold(int amount) {
    next->modifyGold(amount);
}

void Decorator::modifyHP(int amount) {
    next->modifyHP(amount);
}

void Decorator::addBarrierSuite() { next->addBarrierSuite(); }

int Decorator::getRecentX() { return next->getRecentX(); }
int Decorator::getRecentY() { return next->getRecentY(); }

Creature *Decorator::getCreature() { return next->getCreature(); }
