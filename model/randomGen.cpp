#include "randomGen.h"
#include <random>

int randomGen(int start, int end) {
    std::uniform_real_distribution<double> distribution(start, end);
    std::random_device rd;
    std::default_random_engine generator(rd());
    return distribution(generator);
}