//
// Created by kmajdi on 2022-07-14.
//

using namespace std;

#include <fstream>
#include "eventHandler.h"
#include "../view/textDisplay.h"
#include "../model/floor.h"
#include "../model/enemy/Goblin.h"
#include "../model/player/race.h"
#include "../model/randomGen.h"

using namespace std;

EventHandler::EventHandler(std::string readFile, std::string welcomeFile): tDisplay(make_unique<TextDisplay> ()), currentFloor(nullptr),
                                                                           readFile(readFile), welcomeFile(welcomeFile),
                                                                           BarrierSuiteFloorNum(randomGen(1, 6)) {}

EventHandler::~EventHandler() {
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
    if (!currentFloor->hints.empty()) {
        cout << "HINTS:" << endl;
        for (auto hint: currentFloor->hints) {
            cout << hint << endl;
        }
    }
}



void EventHandler::initFloor() {
    ifstream f1 {welcomeFile};
    char race = tDisplay->welcomeScreen(f1);
    string PlayerRace = "";
    Player *p = new Humen(&cin, &cout, &isFinished);
    if (race == 'h') {
        PlayerRace = "Humen";
    } else if (race == 'e') {
        delete p;
        p = new Elf(&cin, &cout, &isFinished);
        PlayerRace = "Elf";
    } else if (race == 'o') {
        delete p;
        p = new Orc(&cin, &cout, &isFinished);
        PlayerRace = "Orc";
    } else if (race == 'd') {
        delete p;
        p = new Dwarf(&cin, &cout, &isFinished);
        PlayerRace = "Dwarf";
    } else {
        delete p;
        isFinished = true;
    }
    
    ifstream f2 {readFile};

    

    bool hasBs = false;
    if (BarrierSuiteFloorNum == floorNum) {
        hasBs = true;
    }
    
    currentFloor = make_unique<Floor>(PlayerRace, hasBs);
    currentFloor->attach(*tDisplay);
    currentFloor->initFloor(f2, p);
    floorNum++;
    setup();
    f1.close();
    f2.close();

}


void EventHandler::nextFloor() {
    Creature *c = currentFloor->getPlayer()->getCreature();
    Player *p  = new Humen(&cin, &cout, &isFinished);
    string pRace = currentFloor->getPlayerRace();
    if (pRace == "Humen") {
        
    } else if (pRace == "Orc") {
        delete p;
        p = new Orc(&cin, &cout, &isFinished);
    } else if (pRace == "Elf") {
        delete p;
        p = new Elf(&cin, &cout, &isFinished);
    } else if (pRace == "Dwarf") {
        delete p;
        p = new Dwarf(&cin, &cout, &isFinished);
    }
    
    p->modifyHP(c->getHP() - p->getHP());
    p->modifyGold(c->getGold() - p->getGold());
    if (c->hasBarrierEffect()) {
        p->addBarrierSuite();
    }
    floorNum++;
    bool hasBs = false;
    if (BarrierSuiteFloorNum == floorNum) {
        hasBs = true;
    }
    currentFloor = make_unique<Floor>(pRace, hasBs);
    currentFloor->attach(*tDisplay);
    ifstream f{readFile};
    currentFloor->initFloor(f, p);
    if (isRandom) {
        setup();
    }
    
    currentFloor->timeForNextFloor = false;
    if (floorNum == 6) {
        isFinished = true;
        return;
    }
}


void EventHandler::setup() {
    currentFloor->setup();
}

void EventHandler::nextTurn() {
    if (currentFloor->timeForNextFloor) {
        nextFloor();
    }

    report();
    currentFloor->takeTurn();
}

bool EventHandler::gameFinished() {
    return isFinished;
}

void EventHandler::showScore() {
    cout << "GAME OVER " << endl;
    cout << "your score is: " << currentFloor->getPlayer()->getGold() << endl;
}



