//
// Created by kmajdi on 2022-07-14.
//

#include "Merchant.h"
#include "floor.h"
#include "randomGen.h"



Merchant::Merchant(): Enemy(30, 70, 5) {
    rep = 'M';
}

void Merchant::move() {
    std::cout << isAgro << std::endl;
    if (isAgro) {
        for (int i = recentX - 1; i <= recentX + 1; i++) {
        std::cout << "merchant wants to attack1" << std::endl;
            for (int j = recentY - 1; j <= recentY + 1; j++) {
            std::cout << fl->isPlayer(fl->whatCreature(i, j)) << std::endl;
                if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatCreature(i, j))) {
                    std::cout << "merchant wants to attack3" << std::endl;
                    attack(fl->whatCreature(i, j), 0);
                    return;
                }
            }
        }
    }

    int command = randomGen(0, 4);
    int newX = recentX;
    int newY = recentY;
    Direction d = directionOfCommand(command, &newX, &newY);
    int count = 0;

    while((fl->getState(newX, newY) != Ground::empty && fl->getState(newX, newY) != Ground::path
           && fl->getState(newX, newY) != Ground::door) || fl->isOccupied(newX, newY)) {
        newX = recentX;
        newY = recentY;
        command = randomGen(0, 4);
        d = directionOfCommand(command, &newX, &newY);
        count++;

        if(count > 30) { return; }
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}

int Merchant::beAttackedBy(Creature *who, int defModifier) {
    isAgro = true;
    
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