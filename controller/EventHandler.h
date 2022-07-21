//
// Created by kmajdi on 2022-07-14.
//
#ifndef CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
#define CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
#include <vector>
#include <string>
#include "Player.h"
class TextDisplay;
class Floor;

class EventHandler {
    TextDisplay *tDisplay;
    Floor *currentFloor;
    std::vector<std::string> log;
public:
    Player *p;
    EventHandler();
    ~EventHandler();
    void initFloor(std::string readFile);
    void setup();
    void nextTurn();
    std::vector<std::string> outLog();
};


#endif //CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
