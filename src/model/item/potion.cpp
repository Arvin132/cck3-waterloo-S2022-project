#include "potion.h"
#include "life.h"
#include "floor.h"
#include "effect.h"

using namespace std;
bool PotionRH::hasBeenDrunk;
bool PotionPH::hasBeenDrunk;
bool PotionBA::hasBeenDrunk;
bool PotionWA::hasBeenDrunk;
bool PotionBD::hasBeenDrunk;
bool PotionWD::hasBeenDrunk;

Potion::Potion(): Item() { }

Potion::~Potion() { }

PotionRH::PotionRH(): Potion() {
    rep = 'P';
    description = " Drank a potion that restores 10 HP. ";
    information = " a potion that restores 10 HP. ";
}

int PotionRH::effect(Life *who) {
    hasBeenDrunk = true;
    who->modifyHP(10);
    return 0;
}

string PotionRH::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}

PotionPH::PotionPH(): Potion() {
    rep = 'P';
    description = " Drank a potion that damges 10 HP. ";
    information = " a potion that damges 10 HP. ";
}

int PotionPH::effect(Life *who) {
    hasBeenDrunk = true;
    if (fl->getPlayerRace() == "Elf") {
        who->modifyHP(10);
    } else {
        who->modifyHP(-10);
    }
    return 0;
}

string PotionPH::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}

PotionBA::PotionBA(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts attack by 5. ";
    information = " a potion that boosts attack by 5. ";
}

int PotionBA::effect(Life *who) {
    hasBeenDrunk = true;
    fl->replace(who , new ModAtk(who, 5));
    return 0;
} 

string PotionBA::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}

PotionWA::PotionWA(): Potion() {
    rep = 'P';
    description = " Drank a potion that decreases attack by 5. ";
    information = " a potion that decreases attack by 5. ";
}

int PotionWA::effect(Life *who) {
    hasBeenDrunk = true;
    if (fl->getPlayerRace() == "Elf") {
        fl->replace(who , new ModAtk(who, 5));
    } else {
        fl->replace(who , new ModAtk(who, -5));
    }
    return 0;
} 

string PotionWA::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}

PotionBD::PotionBD(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts defense by 5. ";
    information = " a potion that boosts defense by 5. ";
}

int PotionBD::effect(Life *who) {
    hasBeenDrunk = true;
    fl->replace(who , new ModDef(who, 5));
    return 0;
} 

string PotionBD::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}

PotionWD::PotionWD(): Potion() {
    rep = 'P';
    description = " Drank a potion that decreases defense by 5. ";
    information = " a potion that decreases defense by 5. ";
}

int PotionWD::effect(Life *who) {
    hasBeenDrunk = true;

    if (fl->getPlayerRace() == "Elf") {
        fl->replace(who , new ModDef(who, 5));
    } else {
        fl->replace(who , new ModDef(who, -5));
    }
    return 0;
} 

string PotionWD::getDescription() {
    if (hasBeenDrunk) {
        return description;
    } else {
        return " an unknown Potion. ";
    }
}
