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
                              p(new Player(&cin, &cout, 100, 50, 10, 10)){}

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
    currentFloor->spawn(new Goblin, 10, 4);
    std::cout << *tDisplay;
    std::cout << "HP: " << p->curHp << endl;
    std::cout << "ATK: " << p->atk << endl;
    std::cout << "Def: " << p->def << endl;
    std::cout << "Gold: " << p->gold << endl;
}

void EventHandler::nextTurn() {
    currentFloor->takeTurn();
    std::cout << *tDisplay;
    std::cout << "HP: " << p->curHp << endl;
    std::cout << "ATK: " << p->atk << endl;
    std::cout << "Def: " << p->def << endl;
    std::cout << "Gold: " << p->gold << endl;
}

bool EventHandler::gameFinished() {
    return p->isFinished();
}




