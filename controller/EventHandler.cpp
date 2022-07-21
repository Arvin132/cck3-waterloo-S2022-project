//
// Created by kmajdi on 2022-07-14.
//
#include <fstream>
#include "EventHandler.h"
#include "../view/textDisplay.h"
#include "../model/floor.h"

using namespace std;

EventHandler::EventHandler(): tDisplay(new TextDisplay()), currentFloor(nullptr),
                              p(new Player(&cin, 10, 10, 10, 10)), log{vector<string>("Player character has spawned. ")}{}

EventHandler::~EventHandler() {
    delete tDisplay;
    delete p;
}

void EventHandler::initFloor(string readFile) {
    ifstream f {readFile};
    if (currentFloor != nullptr) {
        delete currentFloor;
    }
    currentFloor = new Floor(f);
}

void EventHandler::setup() {
    currentFloor->spawn(p, 10, 5);
    std::cout << *tDisplay;
}

void EventHandler::nextTurn() {
    currentFloor->takeTurn();
    std::cout << *tDisplay;;
}

std::vector <std::string> EventHandler::outLog() {
    vector<string> tempLog = log;
    log.clear();
    return tempLog;
}
