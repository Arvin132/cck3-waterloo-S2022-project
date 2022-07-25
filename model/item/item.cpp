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

bool Item::hasPermisson() const{
    return permisson;
}

char Item::getRep() {
    return rep; 
}

std::string Item::getDescription() {
    return description;
}

PickUpable::PickUpable(): Item() {}