//
// Created by kmajdi on 2022-07-14.
//

#include "Dragon.h"
#include "specialItem.h"
#include "floor.h"
#include <cmath>

Dragon::Dragon(DragonHoard *hoard): Enemy(150, 20, 20), hoard(hoard) { 
    rep = 'D';
    hoard->permisson = true;
}

void Dragon::move(int atkMod) {
    for (int i = recentX - 1; i <= recentX + 1 ;i++) {
        for (int j = recentY - 1; j <= recentY + 1; j++) {
            if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatLife(i, j))) {
                attack(fl->whatLife(i, j), atkMod);
                return;
            }
        }
    }
}

int Dragon::beAttackedBy(Life *who, int defModifier) {

    def += defModifier;
    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    curHp -= damage;
    std::cout << "got attacked for " << damage << " Damage" << std::endl;

    if (curHp <= 0) {
        // fear grows on me
        hoard->permisson = true;
        fl->died(this);
        return damage;
    }

    def -= defModifier;
    return damage;
}