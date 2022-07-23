#include "item.h"
#include "Observer.h"

Item::Item(): Subject() {}

Item::~Item() {}


void Item::notifyObservesrs() {
    for (auto ob : observers) {
        ob->notify(*this);
    }
}

int Item::getRecentX() { return recentX; }
int Item::getRecentY() { return recentY; }

char Item::getRep() {
    return rep; 
}

std::string Item::getDescription() {
    return description;
}