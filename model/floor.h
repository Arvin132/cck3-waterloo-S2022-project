#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "Subject.h"
#include "Player.h"
#include "life.h"
class Gold;
class Potion;


enum Ground {nothing =0, empty, Vwall, Hwall, path, door, potion, gold};

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

    void addBlock(int h, int w, Ground type);
    int getLabel();
    void setLabel(int label);
    Block* getSpawnPos();

public:
    Chamber(Floor *owner, int label);
    friend class Floor;
};

class Floor: public Subject {
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;

    std::vector<Life*> living;
    std::vector<Item*> items;
    std::vector<Chamber> chambers;
    

    const int width = 79;
    const int heigth = 25;
    void initChambers();
public:
    Floor(std::istream &in, Player *p, Observer *intialOb);
    ~Floor();
    int getRecentX() override;
    int getRecentY() override;
    Life *getPlayer();
    Ground getState(int posx, int posy);
    void takeTurn();
    void notifyObservesrs() override;
    void spawn(Creature *c, int posx, int posy);
    void spawn(Gold *what, int posx, int posy);
    void spawn(Potion *what, int posx, int posy);
    bool isOccupied(int posx, int posy);
    bool isPlayer(Life *who);
    Life *whatLife(int posx, int posy);
    Item *whatItem(int posx, int posy);
    void Interact(Player *who, Item *what);
    void replace(Life *what, Life *with);
    void gotMoved(int posx, int posy, Direction d);
    void died(Life *who);
};



#endif