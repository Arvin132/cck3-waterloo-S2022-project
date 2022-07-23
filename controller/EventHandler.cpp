//
// Created by kmajdi on 2022-07-14.
//

using namespace std;

#include <fstream>
#include "eventHandler.h"
#include "textDisplay.h"
#include "floor.h"
#include "Goblin.h"
#include "race.h"

using namespace std;

EventHandler::EventHandler(std::string readFile, std::string welcomeFile, bool isRandom): tDisplay(new TextDisplay()), currentFloor(nullptr),
                                                                                          readFile(readFile), welcomeFile(welcomeFile), isRandom(isRandom) {}

EventHandler::~EventHandler() {
    delete currentFloor;
    delete tDisplay;

}

void EventHandler::report() {
    Life *p = currentFloor->getPlayer();
    cout << *tDisplay;
    cout << left << "Race: " << currentFloor->getPlayerRace();
    cout << " Gold " << p->getGold();
    cout << right << " Floor " << floorNum << endl;
    cout << "HP: " << p->getHP() << endl;
    cout << "Atk: " << p->getAtk() << endl;
    cout << "Def: " << p->getDef() << endl;
    cout << "Action: " << p->getCreature()->report() << endl;
}



void EventHandler::initFloor() {
    ifstream f1 {welcomeFile};
    char race = tDisplay->welcomeScreen(f1);
    string PlayerRace = "";
    Player *p = nullptr;
    switch(race) {
        case 'h':
            p = new Humen(&cin, &cout, &isFinished);
            PlayerRace = "Humen";
            break;
        case 'e':
            p = new Elf(&cin, &cout, &isFinished);
            PlayerRace = "Elf";
            break;
        case 'd':
            p = new Dwarf(&cin, &cout, &isFinished);
            PlayerRace = "Dwarf";
            break;
        case 'o':
            p = new Orc(&cin, &cout, &isFinished);
            PlayerRace = "Orc";
            break;
        default:
            isFinished = true;
    }
    ifstream f2 {readFile};

    if (currentFloor != nullptr) {
        delete currentFloor;
    }

    
    currentFloor = new Floor(PlayerRace);
    currentFloor->attach(tDisplay);
    currentFloor->initFloor(f2, p);
    if (isRandom) {
        setup();
    }
    f1.close();
    f2.close();
}

void EventHandler::setup() {
    currentFloor->spawn(new Goblin, 5, 4);
    currentFloor->spawn(new Goblin, 10, 4);
    report();
}

void EventHandler::nextTurn() {
    report();
    
    if  (currentFloor->timeForNextFloor) {
        Creature *c = currentFloor->getPlayer()->getCreature();
        Player *p = dynamic_cast<Player*>(c);
        string pRace = currentFloor->getPlayerRace();
        delete currentFloor;
        currentFloor = new Floor(pRace);
        ifstream f{readFile};
        currentFloor->initFloor(f, p);
        if (isRandom) {
            setup();
        }
    }
    
    currentFloor->takeTurn();
}

bool EventHandler::gameFinished() {
    return isFinished;
}




