//
// Created by kmajdi on 2022-07-14.
//

#ifndef CCK3_WATERLOO_S2022_PROJECT_POTION_H
#define CCK3_WATERLOO_S2022_PROJECT_POTION_H
#include "Decorator.h"

class ModAtk: public Decorator {
    void attack(Creature *other, int atkModifier) override;
    void beAttackedBy(Creature *who, int defModifier) override;
};



class ModDef: public Decorator {
    void attack(Creature *other, int atkModifier) override;
    void beAttackedBy(Creature *who, int defModifier) override;
};



#endif //CCK3_WATERLOO_S2022_PROJECT_POTION_H
