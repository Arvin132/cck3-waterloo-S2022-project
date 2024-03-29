//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
#define CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
#include <iostream>
#include "creature.h"
class Item;
class EventHandler;

class Player: public Creature {
    std::istream *input;
    std::ostream *output;
    bool *gameFinished;
    std::string log = "";
    bool hasBarrierSuite = false;
    public:
        Player(std::istream *input, std::ostream *output, bool *gameState, int hp, int atk, int def, int gold);
        Player(const Player &other);
        void attack(Life *who, int atkMod) override;
        int  beAttackedBy(Life *who, int defModifier) override;
        void beEffectedBy(Item *what) override;
        void addBarrierSuite() override;
        bool hasBarrierEffect() override;
        std::string report() override;
        std::string getInfo() override;
        void move(int atkMod) override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
