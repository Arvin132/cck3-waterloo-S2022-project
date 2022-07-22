//
// Created by kmajdi on 2022-07-14.
//

#include "Dragon.h"
#include "floor.h"
#include "math.h"

Dragon::Dragon(): Enemy(150, 20, 20) {}

void Dragon::move() {
    for (int i = recentX - 1; i <= recentX + 1 ;i++) {
        for (int j = recentY - 1; j <= recentY + 1; j++) {
            if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatCreature(i, j))) {
                attack(fl->whatCreature(i, j), 0);
                return;
            }
        }
    }
}

int Dragon::beAttackedBy(Creature *who, int defModifier) {

    def += defModifier;
    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    curHp -= damage;
    std::cout << "got attacked for " << damage << " Damage" << std::endl;

    if (curHp <= 0) {
        // fear grows on me
        fl->died(this);
        return damage;
    }

    def -= defModifier;
    return damage;
}