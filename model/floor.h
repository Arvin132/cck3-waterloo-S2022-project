#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "subject.h"
#include "creature.h"

enum Ground {nothing =0, empty, Vwall, Hwall, path, door};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Creature*> living;
    const int width = 79;
    const int heigth = 25;

public:
    Floor(std::istream &in, Observer *initialOb);
    ~Floor();
    void takeTurn();
    void notifyObservesrs() override;
    void spawn(Creature *c, int posx, int posy);
    Ground getState(int posx, int posy);
    void gotMoved(int posx, int posy, Direction d);
};

class Chamber {

};

#endif