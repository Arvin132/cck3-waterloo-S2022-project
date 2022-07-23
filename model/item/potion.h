#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
class Life;

class Potion : public Item {
    protected:
        Potion();
    public:
        virtual ~Potion();
};

class PotionRH : public Potion {
    
    inline static bool hasBeenDrunk;
    public:
        PotionRH();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};

class PotionBA : public Potion {
    inline static bool hasBeenDrunk;
    public:
        PotionBA();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};

class PotionBD : public Potion {
    inline static bool hasBeenDrunk;
    public:
        PotionBD();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};

class PotionPH : public Potion {
    inline static bool hasBeenDrunk;
    public:
        PotionPH();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};


class PotionWA : public Potion {
    inline static bool hasBeenDrunk;
    public:
        PotionWA();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};

class PotionWD : public Potion {
    inline static bool hasBeenDrunk;
    public:
        PotionWD();
        bool hasDrunk();
        void effect(Life *who) override;
        std::string getDescription() override;
};


#endif