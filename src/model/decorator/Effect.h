//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_POTION_H
#define CCK3_WATERLOO_S2022_PROJECT_POTION_H
#include "Decorator.h"

class ModAtk: public Decorator {
    int mod;
    public:
        ModAtk(Life *next, int amount);
        void move(int atkModifier) override;
        int beAttackedBy(Life *who, int defModifier) override;
        int getAtk() override;
        int getDef() override;
};



class ModDef: public Decorator {
    int mod;
    public:
        ModDef(Life *next, int amount);
        void move(int atkModifier) override;
        int beAttackedBy(Life *who, int defModifier) override;
        int getAtk() override;
        int getDef() override;
};



#endif //CCK3_WATERLOO_S2022_PROJECT_POTION_H
