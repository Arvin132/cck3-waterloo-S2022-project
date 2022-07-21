#ifndef __TEXT_D__
#define __TEXT_D__
#include "observer.h"
#include <vector>
#include <iostream>


class EventHandler;

class TextDisplay: public Observer {
    std::vector<std::vector<char>> display;
    const int width = 79;
    const int height = 25;
    EventHandler *eventHandler;
  public:
    TextDisplay(Floor *floor);
    void virtual notify(Creature &who) override;
    void virtual notify(Floor &who) override;
    friend std::ostream &operator<<(std::ostream &out, TextDisplay td);
};

#endif