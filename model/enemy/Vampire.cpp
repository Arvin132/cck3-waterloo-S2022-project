//
// Created by kmajdi on 2022-07-14.
//

#include "Vampire.h"
#include "floor.h"
#include "gold.h"

Vampire::Vampire():Enemy(50, 25, 25) {
    rep = 'V';
}

Vampire::~Vampire() {
    fl->spawn(new Gold(1), recentX, recentY);
}

void Vampire::attack(Life *other, int atkModifier) {
    atk += atkModifier;
    curHp += other->beAttackedBy(this, 0) / 2;

    atk -= atkModifier;
}