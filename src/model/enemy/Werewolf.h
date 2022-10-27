//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_WEREWOLF_H
#define CCK3_WATERLOO_S2022_PROJECT_WEREWOLF_H
#include "Enemy.h"

class Werewolf: public Enemy {
    public:
        Werewolf();
        ~Werewolf();
        std::string getInfo() override;
};


#endif //CCK3_WATERLOO_S2022_PROJECT_WEREWOLF_H
