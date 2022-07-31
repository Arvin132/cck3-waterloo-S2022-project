#include "item.h"
#include "Observer.h"

Item::Item(): Subject() {}

Item::~Item() {}


void Item::notifyObservesrs() {
    for (auto ob : observers) {
        ob->notify(*this);
    }
}

bool Item::hasPermisson() const{
    return permisson;
}

char Item::getRep() {
    return rep; 
}

std::string Item::getDescription() {
    return description;
}

std::string Item::getInfo() {
    if (permisson) {
        return information;
    } else {
        return information + " it is protected by something. ";
    }
}

PickUpable::PickUpable(): Item() {}