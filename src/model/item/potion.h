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
    
    static bool hasBeenDrunk;
    public:
        PotionRH();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};

class PotionBA : public Potion {
    static bool hasBeenDrunk;
    public:
        PotionBA();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};

class PotionBD : public Potion {
    static bool hasBeenDrunk;
    public:
        PotionBD();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};

class PotionPH : public Potion {
    static bool hasBeenDrunk;
    public:
        PotionPH();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};


class PotionWA : public Potion {
    static bool hasBeenDrunk;
    public:
        PotionWA();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};

class PotionWD : public Potion {
    static bool hasBeenDrunk;
    public:
        PotionWD();
        bool hasDrunk();
        int effect(Life *who) override;
        std::string getDescription() const override;
        std::string getInfo() const override;
};


#endif