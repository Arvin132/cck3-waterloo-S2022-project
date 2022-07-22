//
// Created by kmajdi on 2022-07-14.
//

using namespace std;

#include <fstream>
#include "eventHandler.h"
#include "textDisplay.h"
#include "floor.h"
#include "Goblin.h"

using namespace std;

EventHandler::EventHandler(): tDisplay(new TextDisplay()), currentFloor(nullptr),
                              p(new Player(&cin, 10, 100, 10, 10)){}

EventHandler::~EventHandler() {
    delete tDisplay;
    delete p;
}

void EventHandler::initFloor(string readFile) {
    ifstream f {readFile};
    if (currentFloor != nullptr) {
        delete currentFloor;
    }
    currentFloor = new Floor(f, p, tDisplay);
}

void EventHandler::setup() {
    currentFloor->spawn(new Goblin, 5, 4);
    std::cout << *tDisplay;
    std::cout << "HP: " << p->hp << endl;
    std::cout << "ATK: " << p->atk << endl;
    std::cout << "Def: " << p->def << endl;
}

void EventHandler::nextTurn() {
    currentFloor->takeTurn();
    std::cout << *tDisplay;
    std::cout << "HP: " << p->hp << endl;
    std::cout << "ATK: " << p->atk << endl;
    std::cout << "Def: " << p->def << endl;
}

bool EventHandler::gameFinished() {
    return p->isFinished();
}


