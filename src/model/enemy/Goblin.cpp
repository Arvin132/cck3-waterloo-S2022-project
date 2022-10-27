//
// Created by kmajdi on 2022-07-14.
//

#include "Goblin.h"
#include "../item/gold.h"
#include "../floor.h"

Goblin::Goblin(): Enemy(70, 5, 10), stolen(0) { rep = 'N';}

Goblin::~Goblin() {
    fl->spawn(new Gold(1 + stolen), recentX, recentY);
}

void Goblin::attack(Life *other, int atkModifier) {
    atk += atkModifier;
    other->modifyGold(-1);
    stolen++;
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}

std::string Goblin::getInfo() {
    return " a Goblin. HP: " + std::to_string(curHp) + " DEF: " + std::to_string(def) + " ATK: " + std::to_string(atk) 
    + ". has gold stealing.";
}
