//
// Created by kmajdi on 2022-07-14.
//

#include "Troll.h"
#include "floor.h"
#include "randomGen.h"



Troll::Troll(): Enemy(120, 25, 15) {
    rep = 'T';
}

void Troll::move() {
    modifyHP(5);

    for (int i = recentX - 1; i <= recentX + 1 ;i++) {
        for (int j = recentY - 1; j <= recentY + 1; j++) {
            if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatCreature(i, j))) {
                attack(fl->whatCreature(i, j), 0);
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
        command = randomGen(0, 4);
        d = directionOfCommand(command, &newX, &newY);
        count++;

        if(count > 30) { return; }
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}