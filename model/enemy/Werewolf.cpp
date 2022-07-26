//
// Created by kmajdi on 2022-07-14.
//

#include "Werewolf.h"
#include "floor.h"
#include "gold.h"

Werewolf::Werewolf(): Enemy(120, 30, 5) {
    rep = 'W';
}

Werewolf::~Werewolf() {
    fl->spawn(new Gold(1), recentX, recentY);
}
