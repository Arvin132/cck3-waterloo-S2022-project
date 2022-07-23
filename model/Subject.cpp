//
// Created by kmajdi on 2022-07-14.
//
#include "observer.h"
#include "subject.h"

Subject::~Subject() { }


void Subject::attach(Observer *ob) {
    observers.emplace_back(ob);
}


void Subject::detach(Observer *ob) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == ob) {
            observers.erase(it);
            break;
        }
    }
}

