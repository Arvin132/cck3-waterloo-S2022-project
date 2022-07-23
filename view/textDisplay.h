#ifndef __TEXT_D__
#define __TEXT_D__
#include "Observer.h"
#include <vector>
#include <iostream>


class TextDisplay: public Observer {
    std::vector<std::vector<char>> display;
    const int width = 79;
    const int heigth = 25;
  public:
    TextDisplay();
    void notify(Creature &who) override;
    void notify(Floor &who) override;
    void notify(Item &who) override;
    char welcomeScreen(std::istream &input);
    friend std::ostream &operator<<(std::ostream &out, TextDisplay td);
};

#endif