//
// Created by kmajdi on 2022-07-14.
//

#include "Goblin.h"

Goblin::Goblin(): Enemy(70, 5, 10) { rep = 'N';}


void Goblin::attack(Life *other, int atkModifier) {
    atk += atkModifier;
    other->modifyGold(-1);
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}