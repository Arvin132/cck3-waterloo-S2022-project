//
// Created by kmajdi on 2022-07-14.
//

#include "Troll.h"
#include "../floor.h"
#include "../randomGen.h"
#include "../item/gold.h"


Troll::Troll(): Enemy(120, 25, 15) {
    rep = 'T';
}

Troll::~Troll() {
    fl->spawn(new Gold(1), recentX, recentY);
}

void Troll::move(int atkMod) {
    modifyHP(5);

    for (int i = recentX - 1; i <= recentX + 1 ;i++) {
        for (int j = recentY - 1; j <= recentY + 1; j++) {
            if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatLife(i, j))) {
                attack(fl->whatLife(i, j), atkMod);
                return;
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

std::string Troll::getInfo() {
    return " a Troll. HP: " + std::to_string(curHp) + " DEF: " + std::to_string(def) + " ATK: " + std::to_string(atk) + 
    ". has HP regeneration.";
}
