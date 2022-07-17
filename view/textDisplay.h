#ifndef __TEXT_D__
#define __TEXT_D__
#include "observer.h"
#include <vector>
#include <iostream>


class TextDisplay: public Observer {
    std::vector<std::vector<char>> display;
    const int width = 79;
    const int heigth = 25;
  public:
    TextDisplay();
    void virtual notify(Creature &who) override;
    void virtual notify(Floor &who) override;
    friend std::ostream &operator<<(std::ostream &out, TextDisplay td);
};

#endif