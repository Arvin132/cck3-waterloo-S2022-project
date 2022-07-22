//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
#define CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
#include <iostream>
#include "creature.h"
class EventHandler;

class Player: public Creature {
    std::istream *input;
    
    bool finished = false;
    public:
        Player(std::istream *input, int hp, int atk, int def, int gold);
        void virtual attack(Creature *other, int atkModifier) override;
        void virtual beAttackedBy(Creature *who, int defModifier) override;
        void virtual modifyHP(int amount) override;
        void virtual modifyGold(int amount) override;
        bool isFinished();
        void virtual move() override;
        friend class EventHandler;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_PLAYER_H
