#include "potion.h"
#include "life.h"
#include "floor.h"
#include "effect.h"

using namespace std;

Potion::Potion(): Item() { }

Potion::~Potion() { }

PotionRH::PotionRH(): Potion() {
    rep = 'P';
    description = " Drank a potion that restores 10 HP. ";
}

void PotionRH::effect(Life *who) {
    hasBeenDrunk = true;
    who->modifyHP(10);
}

PotionPH::PotionPH(): Potion() {
    rep = 'P';
    description = " Drank a potion that Damges 10 HP. ";
}

void PotionPH::effect(Life *who) {
    hasBeenDrunk = true;
    if (fl->getPlayerRace() == "Elf") {
        who->modifyHP(10);
    } else {
        who->modifyHP(-10);
    }
}

PotionBA::PotionBA(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts attack by 5. ";
}

void PotionBA::effect(Life *who) {
    hasBeenDrunk = true;
    fl->replace(who , new ModAtk(who, 5));
} 

PotionWA::PotionWA(): Potion() {
    rep = 'P';
    description = " Drank a potion that decreases attack by 5. ";
}

void PotionWA::effect(Life *who) {
    hasBeenDrunk = true;
    if (fl->getPlayerRace() == "Elf") {
        fl->replace(who , new ModAtk(who, 5));
    } else {
        fl->replace(who , new ModAtk(who, -5));
    }
} 


PotionBD::PotionBD(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts defense by 5. ";
}

void PotionBD::effect(Life *who) {
    hasBeenDrunk = true;
    fl->replace(who , new ModDef(who, 5));
} 



PotionWD::PotionWD(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts defense by 5. ";
}

void PotionWD::effect(Life *who) {
    hasBeenDrunk = true;

    if (fl->getPlayerRace() == "Elf") {
        fl->replace(who , new ModDef(who, 5));
    } else {
        fl->replace(who , new ModDef(who, -5));
    }
} 