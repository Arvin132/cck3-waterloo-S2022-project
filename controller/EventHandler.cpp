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



void EventHandler::initFloor(string readFile, string welcomeFile) {
    ifstream f1 {welcomeFile};
    PlayerRace = tDisplay->welcomeScreen(f1);
    ifstream f2 {readFile};
    if (currentFloor != nullptr) {
        delete currentFloor;
    }
    currentFloor = new Floor(f2, new Player(&cin, &cout, &isFinished, 100, 50, 10, 10), tDisplay);
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




