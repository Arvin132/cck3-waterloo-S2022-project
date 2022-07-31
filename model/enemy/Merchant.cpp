//
// Created by kmajdi on 2022-07-14.
//

#include "Merchant.h"
#include "gold.h"
#include "floor.h"
#include "randomGen.h"

bool Merchant::isAgro;

Merchant::Merchant(): Enemy(30, 70, 5) {
    rep = 'M';
}

Merchant::~Merchant() {
    fl->spawn(new Gold(4), recentX, recentY);
}

void Merchant::move(int atkMod) {
    if (isAgro) {
        for (int i = recentX - 1; i <= recentX + 1; i++) {
            for (int j = recentY - 1; j <= recentY + 1; j++) {
                if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatLife(i, j))) {
                    attack(fl->whatLife(i, j), atkMod);
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

int Merchant::beAttackedBy(Life *who, int defModifier) {
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

std::string Merchant::getInfo() {
    std::string someStr =  " a Merchant. HP: " + std::to_string(curHp) + " DEF: " + std::to_string(def) + " ATK: " + std::to_string(atk) + ".";
    if (isAgro) {
        someStr += " He is Agrresive";
    }
    return someStr;
}