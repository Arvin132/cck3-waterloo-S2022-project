#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "subject.h"
#include "Player.h"
#include "creature.h"

enum Ground {nothing =0, empty, Vwall, Hwall, path, door, item};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Creature*> living;
    // std::vector<Item> items;
    const int width = 79;
    const int heigth = 25;

public:
    Floor(std::istream &in, Player *p, Observer *intialOb);
    ~Floor();
    void takeTurn();
    void notifyObservesrs() override;
    void spawn(Creature *c, int posx, int posy);
    Ground getState(int posx, int posy);
    bool isOccupied(int posx, int posy);
    Creature *whatCreature(int posx, int posy);
    bool isPlayer(Creature *who);
    //Item *whatItem(int posx, int posy);
    //void Interact(Player *who, Item *what);
    void gotMoved(int posx, int posy, Direction d);
    void died(Creature *who);
};

class Chamber {

};

#endif