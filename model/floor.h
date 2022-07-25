#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "Subject.h"
#include "Player.h"
#include "life.h"
class Gold;
class Potion;
class PickUpable;


enum Ground {nothing =0, empty, Vwall, Hwall, path, door, potion, item};

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
    Pos getSpawnPos();

public:
    Chamber(Floor *owner, int label);
    friend class Floor;
};

class Floor: public Subject {
    std::string PlayerRace;
    std::vector<std::vector<Ground>> theGrid;
    std::vector<std::vector<bool>> occupied;
    std::vector<Life*> living;
    std::vector<Item*> items;
    std::vector<Chamber> chambers;
    bool hasBS;
    

    const int width = 79;
    const int heigth = 25;
    void initChambers();
public:
    bool timeForNextFloor;
    Floor(std::string PlayerRace, bool hasBS);
    ~Floor();
    void initFloor(std::istream &in, Player *p);
    void initSpecificFloor(std::istream &in, Player *p);
    int getRecentX() override;
    int getRecentY() override;
    Life *getPlayer();
    std::string getPlayerRace();
    Ground getState(int posx, int posy);
    void setup();
    void takeTurn();
    void notifyObservesrs() override;
    void spawn(Creature *c, int posx, int posy);
    void spawn(PickUpable *what, int posx, int posy);
    void spawn(Potion *what, int posx, int posy);
    void spawnStairs();
    bool isOccupied(int posx, int posy);
    bool isPlayer(Life *who);
    Life *whatLife(int posx, int posy);
    Item *whatItem(int posx, int posy);
    void Interact(Player *who, Item *what);
    void replace(Life *what, Life *with);
    void gotMoved(int posx, int posy, Direction d);
    void died(Life *who);
    void clearFloor();
};



#endif