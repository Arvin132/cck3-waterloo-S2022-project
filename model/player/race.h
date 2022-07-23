#ifndef __RACE_H__
#define __RACE_H__
#include "player.h"

class Humen: public Player {
    public:
        Humen(std::istream *input, std::ostream *output, bool *gameState);
};

class Orc: public Player {
    public:
        Orc(std::istream *input, std::ostream *output, bool *gameState);
        void modifyGold(int amount) override;
};


class Elf: public Player {
    public:
        Elf(std::istream *input, std::ostream *output, bool *gameState);
};

class Dwarf: public Player {
    public:
        Dwarf(std::istream *input, std::ostream *output, bool *gameState);
        void modifyGold(int amount) override;
};

#endif