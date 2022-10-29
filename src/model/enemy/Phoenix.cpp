//
// Created by kmajdi on 2022-07-14.
//

#include "Phoenix.h"
#include "../floor.h"
#include "../item/gold.h"

Phoenix::Phoenix():Enemy(50, 35, 20) {
    rep = 'X';
}

Phoenix::~Phoenix() {
    fl->spawn(new Gold(1), recentX, recentY);
}

std::string Phoenix::getInfo() {
    return " a Phoenix. HP: " + std::to_string(curHp) + " DEF: " + std::to_string(def) + " ATK: " + std::to_string(atk) + ". ";
}
