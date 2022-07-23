#include "gold.h"
#include "creature.h"
#include <string>

Gold::Gold(int amount): Item() , amount(amount){
    rep = 'G';
    description = " Picked up " + std::to_string(amount) + " Gold";
} 

void Gold::effect(Life *who) {
    who->modifyGold(amount);
}