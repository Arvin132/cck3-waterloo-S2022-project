#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "subject.h"
#include "Player.h"
#include "creature.h"

enum Ground {nothing =0, empty, Vwall, Hwall, path, door, item};

struct Pos {
    int x, y;
};

struct Block {
    Pos pos;
    int *roomLabel;
    Ground type;
};

class Chamber {
        int label;
        Floor *floor;
        std::vector<Block*> blocks;
        Chamber(Floor *owner);
        void addBlock(int h, int w, Ground type);
        int getLabel();
        void setLabel(int label);
        Block* getSpawnPos();
        friend class Floor;
};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Creature*> living;
    std::vector<Chamber> chambers;
    // std::vector<Item> items;
    const int width = 79;
    const int heigth = 25;
    void initChambers();
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



#endif