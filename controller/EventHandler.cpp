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

EventHandler::EventHandler(std::string readFile, std::string welcomeFile, bool isRandom): tDisplay(make_unique<TextDisplay> ()), currentFloor(nullptr),
                                                                                          readFile(readFile), welcomeFile(welcomeFile), isRandom(isRandom) {}

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
}



void EventHandler::initFloor() {
    ifstream f1 {welcomeFile};
    char race = tDisplay->welcomeScreen(f1);
    string PlayerRace = "";
    Player p = Humen(&cin, &cout, &isFinished);
    switch(race) {
        case 'h':
            PlayerRace = "Humen";
            break;
        case 'e':
            p = Elf(&cin, &cout, &isFinished);
            PlayerRace = "Elf";
            break;
        case 'd':
            p = Dwarf(&cin, &cout, &isFinished);
            PlayerRace = "Dwarf";
            break;
        case 'o':
            p = Orc(&cin, &cout, &isFinished);
            PlayerRace = "Orc";
            break;
        default:
            isFinished = true;
    }
    ifstream f2 {readFile};

    

                    
    currentFloor = make_unique<Floor>(PlayerRace, true);
    currentFloor->attach(*tDisplay);
    currentFloor->initFloor(f2, move(p));
    // if (isRandom) {
    //     setup();
    // }
    f1.close();
    f2.close();
}

void EventHandler::setup() {
    currentFloor->setup();
}

void EventHandler::nextTurn() {
    
    
    if (currentFloor->timeForNextFloor) {
        Creature *c = currentFloor->getPlayer()->getCreature();
        Player p = Player(&cin, &cout, &isFinished, c->getHP(), c->getAtk(), c->getDef(), c->getGold());
        string pRace = currentFloor->getPlayerRace();
        currentFloor = make_unique<Floor>(pRace, true);
        currentFloor->attach(*tDisplay);
        ifstream f{readFile};
        currentFloor->initFloor(f, move(p));
        if (isRandom) {
            setup();
        }
        floorNum++;
        currentFloor->timeForNextFloor = false;
        if (floorNum == 6) {
            isFinished = true;
            return;
        }
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



