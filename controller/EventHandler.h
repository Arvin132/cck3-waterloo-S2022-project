//
// Created by kmajdi on 2022-07-14.
//
#ifndef CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
#define CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
#include <vector>
#include <string>
#include <memory>
#include "Player.h"
class TextDisplay;
class Floor;

class EventHandler {
    std::unique_ptr<TextDisplay> tDisplay;
    std::unique_ptr<Floor> currentFloor;
    std::string readFile;
    std::string welcomeFile;
    bool isRandom;
    int floorNum = 1;
    int BarrierSuiteFloorNum;
    bool isFinished = false;
public:
    EventHandler(std::string readFile, std::string welcomeFile);
    ~EventHandler();
    void initFloor();
    void nextFloor();
    void setup();
    void nextTurn();
    void report();
    bool gameFinished();
    bool isPlayer(Creature *other);
    void showScore();
};


#endif //CCK3_WATERLOO_S2022_PROJECT_EVENTHANDLER_H
