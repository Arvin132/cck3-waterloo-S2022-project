//
// Created by kmajdi on 2022-07-14.
//

#include "Werewolf.h"
#include "../floor.h"
#include "../item/gold.h"

Werewolf::Werewolf(): Enemy(120, 30, 5) {
    rep = 'W';
}

Werewolf::~Werewolf() {
    fl->spawn(new Gold(1), recentX, recentY);
}

std::string Werewolf::getInfo() {
    return " a Werewolf. HP: " + std::to_string(curHp) + " DEF: " + std::to_string(def) + " ATK: " + std::to_string(atk) + ".";
}
