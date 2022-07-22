//
// Created by kmajdi on 2022-07-14.
//

#include "Merchant.h"
#include "floor.h"
#include "randomGen.h"

Direction directionOfCommand(int d, int *newX, int *newY) {
    switch (d) {
        case 0:
            *newY -= 1;
            return Direction::N;
        case 1:
            *newY += 1;
            return Direction::S;
        case 2:
            *newX += 1;
            return Direction::E;
        case 3:
            *newX -= 1;
            return Direction::W;
    }
}

Merchant::Merchant(): Enemy(30, 70, 5) {
    rep = 'M';
}

void Merchant::move() {
    if (isAgro) {
        for (int i = recentX - 1; i <= recentX + 1 ;i++) {
            for (int j = recentY - 1; j <= recentY + 1; j++) {
                if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatCreature(i, j))) {
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
        command = randomGen(0, 4);
        d = directionOfCommand(command, &newX, &newY);
        count++;

        if(count > 30) { return; }
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}

void Merchant::beAttackedBy(Creature *who, int defModifier) {
    isAgro = true;
    
    def += defModifier;
    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    hp -= damage;
    std::cout << "got attacked for " << damage << " Damage" << std::endl;

    if (hp <= 0) {
        // fear grows on me
        return fl->died(this);
    }

    def -= defModifier;
}