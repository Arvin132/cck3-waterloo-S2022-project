//
// Created by kmajdi on 2022-07-14.
//

using namespace std;

#include <fstream>
#include <iomanip>
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

void EventHandler::report() {
    cout << *tDisplay;
    cout << "Race: " << p->race;
    cout << " Gold" << p->gold;
    cout << right << "Floor" << floorNum << endl;
    cout << "HP: " << p->curHp << endl;
    cout << "Atk: " << p->atk << endl;
    cout << "Def: " << p->def << endl;
    cout << "Action: " << p->report() << endl;
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
    report();
}

void EventHandler::nextTurn() {
    currentFloor->takeTurn();
    report();
}

bool EventHandler::gameFinished() {
    return p->isFinished();
}




