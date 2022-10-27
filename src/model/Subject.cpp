//
// Created by kmajdi on 2022-07-14.
//
#include "Observer.h"
#include "Subject.h"

Subject::~Subject() { }


void Subject::attach(Observer &ob) {
    observers.emplace_back(&ob);
}

int Subject::getRecentX() { return recentX; }
int Subject::getRecentY() { return recentY; }


void Subject::detach(Observer &ob) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == &ob) {
            observers.erase(it);
            break;
        }
    }
}

