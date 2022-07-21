#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "../observer/Subject.h"
#include "creature/creature.h"

class Player;

enum Ground {nothing =0, empty, Vwall, Hwall, path, door, item};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Creature*> living;
    // std::vector<Item> items;
    const int width = 79;
    const int height = 25;

public:
    Floor(std::istream &in);
    ~Floor();
    void takeTurn();
    void notifyObservers() override;
    void spawn(Creature *c, int posx, int posy);
    Ground getState(int posx, int posy);
    bool isOccupied(int posx, int posy);
    //Item *whatItem(int posx, int posy);
    //void Interact(Player *who, Item *what);
    void gotMoved(int posx, int posy, Direction d);
};

class Chamber {

};

#endif