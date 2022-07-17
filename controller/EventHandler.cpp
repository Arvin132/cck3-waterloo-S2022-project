//
// Created by kmajdi on 2022-07-14.
//
#include <fstream>
#include "eventHandler.h"
#include "textDisplay.h"
#include "floor.h"

using namespace std;

EventHandler::EventHandler(): display(new TextDisplay()), currentFloor(nullptr),
                              p(new Player()){}

EventHandler::~EventHandler() {
    delete display;
    delete p;
}

void EventHandler::initFloor(string readFile) {
    ifstream f {readFile};
    if (currentFloor != nullptr) {
        delete currentFloor;
    }
    currentFloor = new Floor(f);
    currentFloor->attach(display);
    currentFloor->notifyObservesrs();
    std::cout << *display;
}



