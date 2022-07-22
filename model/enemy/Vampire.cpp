//
// Created by kmajdi on 2022-07-14.
//

#include "Vampire.h"

Vampire::Vampire():Enemy(50, 25, 25) {
    rep = 'V';
}

void Vampire::attack(Creature *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);
    curHp += atk / 2;

    atk -= atkModifier;
}