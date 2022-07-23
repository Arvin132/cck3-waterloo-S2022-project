//
// Created by kmajdi on 2022-07-14.
//

using namespace std;

#include <fstream>
#include "eventHandler.h"
#include "textDisplay.h"
#include "../model/floor.h"
#include "../model/enemy/Goblin.h"

using namespace std;

EventHandler::EventHandler(): tDisplay(new TextDisplay()), currentFloor(nullptr), PlayerRace("Humen") {}

EventHandler::~EventHandler() {
    delete tDisplay;
    delete currentFloor;
}

void EventHandler::report() {
    Life *p = currentFloor->getPlayer();
    cout << *tDisplay;
    cout << left << "Race: " << PlayerRace;
    cout << " Gold " << p->getGold();
    cout << right << " Floor " << floorNum << endl;
    cout << "HP: " << p->getHP() << endl;
    cout << "Atk: " << p->getAtk() << endl;
    cout << "Def: " << p->getDef() << endl;
    cout << "Action: " << p->getCreature()->report() << endl;
}

void EventHandler::initFloor(string readFile) {
    ifstream f {readFile};
    if (currentFloor != nullptr) {
        delete currentFloor;
    }
    currentFloor = new Floor(f, new Player(&cin, &cout, &isFinished, 100, 50, 10, 10), tDisplay);
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
    return isFinished;
}




