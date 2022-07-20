#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "subject.h"
#include "../creature/creature.h"
#include <iostream>

enum Ground {nothing =0, empty, Vwall, Hwall, path, door, item};

struct Pos {
    int x, y;
};

struct Block {
    Pos pos;
    int *roomLabel;
    Ground type;
};

class Floor;

class Chamber {
    int label;
    Floor *floor;
    std::vector<Block*> blocks;
public:
    Chamber(Floor *ownedBy);
    ~Chamber();
    void addBlock(int h, int w, Ground type);
    int getLabel();
    void setLabel(int label);
    Block* getSpawnPos();
};



class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Creature*> living;
    std::vector<Chamber> chambers;
    // std::vector<Item> items;
    const int width = 79;
    const int height = 25;
    void initChambers();
public:
    Floor(std::istream &in);
    ~Floor();
    void takeTurn();
    void notifyObservesrs() override;
    void spawn(Creature *c, int posx, int posy);
    Ground getState(int posx, int posy);
    bool isOccupied(int posx, int posy);
    //Item *whatItem(int posx, int posy);
    //void Interact(Player *who, Item *what);
    void gotMoved(int posx, int posy, Direction d);
};



class Creature;


#endif