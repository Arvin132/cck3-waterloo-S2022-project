#include "race.h"
#include <cmath>

Humen::Humen(std::istream *input, std::ostream *output, bool *gameState): Player(input, output, gameState, 140, 20, 20, 50) {}

Elf::Elf(std::istream *input, std::ostream *output, bool *gameState): Player(input, output, gameState, 140, 30, 10, 50) {}

Orc::Orc(std::istream *input, std::ostream *output, bool *gameState): Player(input, output, gameState, 180, 30, 25, 50) {}
void Orc::modifyGold(int amount) {
    double g = amount;
    gold += ceil(g / 2);
}

Dwarf::Dwarf(std::istream *input, std::ostream *output, bool *gameState): Player(input, output, gameState, 100, 20, 30, 50) {}

void Dwarf::modifyGold(int amount) {
    gold += 2 * amount;
}
