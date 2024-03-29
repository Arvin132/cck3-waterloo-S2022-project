#include "gold.h"
#include "creature.h"
#include <string>

Gold::Gold(int amount): PickUpable() , amount(amount){
    rep = 'G';
    description = " Picked up " + std::to_string(amount) + " Gold. ";
    information = " Gold Pile with " + std::to_string(amount) + " Coins. ";
} 

int Gold::effect(Life *who) {
    who->modifyGold(amount);
    return 0;
}