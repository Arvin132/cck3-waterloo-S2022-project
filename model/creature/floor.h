#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "subject.h"
#include "creature.h"

enum Ground {nothing =0, empty, Vwall, Hwall, item, occupied, path, door};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<Creature> living;
    const int width = 79;
    const int heigth = 25;
    int recentX = 0;
    int recentY = 0;

public:
    Floor(std::istream &in);
    ~Floor();
    void notifyObservesrs() override;
    void spawn(Creature &c);
    bool validMove(int posx, int posy, Direction d);
    Ground getState(int posx, int posy);
    int getRecentX();
    int getRecentY();
};

class Chamber {

};

#endif