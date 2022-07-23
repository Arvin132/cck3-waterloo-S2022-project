#include "potion.h"
#include "creature.h"
#include "floor.h"

Potion::Potion(): Item() { }

Potion::~Potion() { }

PotionRH::PotionRH(): Potion() {
    rep = 'P';
    description = " Drank a potion that restores 10 HP. ";
}

bool PotionRH::hasDrunk() {
    return hasBeenDrunk;
}

void PotionRH::effect(Creature *who) {
    who->modifyHP(10);
}

PotionPH::PotionPH(): Potion() {
    rep = 'P';
    description = " Drank a potion that Damges 10 HP. ";
}

void PotionPH::effect(Creature *who) {
    who->modifyHP(-10);
}

bool PotionPH::hasDrunk() {
    return hasBeenDrunk;
}

PotionBA::PotionBA(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts attack by 5. ";
}

void PotionBA::effect(Creature *who) {
    
} 

bool PotionBA::hasDrunk() {
    return hasBeenDrunk;
}

PotionWA::PotionWA(): Potion() {
    rep = 'P';
    description = " Drank a potion that decreases attack by 5. ";
}

void PotionWA::effect(Creature *who) {
    
} 

bool PotionWA::hasDrunk() {
    return hasBeenDrunk;
}

PotionBD::PotionBD(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts defense by 5. ";
}

void PotionBD::effect(Creature *who) {
    
} 

bool PotionBD::hasDrunk() {
    return hasBeenDrunk;
}

PotionWD::PotionWD(): Potion() {
    rep = 'P';
    description = " Drank a potion that boosts defense by 5. ";
}

void PotionWD::effect(Creature *who) {
    
} 

bool PotionWD::hasDrunk() {
    return hasBeenDrunk;
}

