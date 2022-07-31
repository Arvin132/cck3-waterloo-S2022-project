#include <string>
#include <iostream>
#include "floor.h"
#include "Subject.h"
#include "Observer.h"
#include "creature.h"
#include "Goblin.h"
#include "Werewolf.h"
#include "Dragon.h"
#include "Troll.h"
#include "Dragon.h"
#include "Vampire.h"
#include "Merchant.h"
#include "Phoenix.h"
#include "gold.h"
#include "potion.h"
#include "specialItem.h"
#include "randomGen.h"

using namespace std;

Floor::Floor(string PlayerRace, bool hasBS): Subject(), PlayerRace(PlayerRace), theGrid(vector<vector<Ground>> {}),
                                             occupied(vector<vector<bool>> {}), living(vector<Life*> {}), chambers{vector<Chamber*>()}, hasBS(hasBS){}

Floor::~Floor() {
    for (auto ch : chambers) {
        delete ch;
    }
    clearFloor();
    occupied.clear();
    theGrid.clear();
}

void Floor::initFloor(std::istream &in, Player *p) {
    char input = ' ';
    for (int j = 0; j < heigth; j++) {
        theGrid.emplace_back(vector<Ground> {});
        occupied.emplace_back(vector<bool> {});
        string s;
        getline(in ,s);
        for (int i = 0; i < width; i++) {
            input = s[i];
            switch (input) {
                case ' ' :
                    theGrid[j].emplace_back(Ground::nothing);
                    break;
                case '-' :
                    theGrid[j].emplace_back(Ground::Hwall);
                    break;
                case '|' :
                    theGrid[j].emplace_back(Ground::Vwall);
                    break;
                case '.' :
                    theGrid[j].emplace_back(Ground::empty);
                    break;
                case '#' :
                    theGrid[j].emplace_back(Ground::path);
                    break;
                case '+' :
                    theGrid[j].emplace_back(Ground::door);
                    break;
                default :
                    theGrid[j].emplace_back(Ground::empty);
                    break;
            }

            occupied[j].emplace_back(false);

            recentX = i;
            recentY = j;
            notifyObservesrs();
        }
    }
    initChambers();
    stairsCh = randomGen(0, 5);
    int r = randomGen(0, 5);
    while (r == stairsCh) {
        r = randomGen(0, 5);
    }
    Pos place = chambers[r]->getSpawnPos();
    spawn(p, place.y, place.x);
    for (auto it : items) {
        it->notifyObservesrs();
    }
}

void Floor::setup() {
    // spawning the enemies
    for (int i = 0; i < 20; i++) {
        int r = randomGen(0, 5);
        Pos place = chambers[r]->getSpawnPos();
        int type = randomGen(0, 18);

        switch(type) {
            case 0: case 1: case 2: case 3:
                spawn(new Werewolf(), place.y, place.x);
                break;
            case 4: case 5: case 6:
                spawn(new Vampire(), place.y, place.x);
                break;
            case 7: case 8: case 9: case 10: case 11:
                spawn(new Goblin(), place.y, place.x);
                break;
            case 12: case 13:
                spawn(new Troll(), place.y, place.x);
                break;
            case 14: case 15:
                spawn(new Phoenix(), place.y, place.x);
                break;
            case 16: case 17:
                spawn(new Merchant(), place.y, place.x);
                break;
        }
    }

    int compassOwnerNum = randomGen(1, living.size());
    compassOwner = living[compassOwnerNum];
    cout << "HINT: a " << compassOwner->getRep() << " has the compass " << endl;
    // spawning the Potions
    for (int i = 0; i < 10; i++) {
        int r = randomGen(0, 5);
        Pos place = chambers[r]->getSpawnPos();
        int type = randomGen(0, 6);

        switch(type) {
            case 0:
                spawn(new PotionRH(), place.y, place.x);
                break;
            case 1:
                spawn(new PotionPH(), place.y, place.x);
                break;
            case 2:
                spawn(new PotionBA(), place.y, place.x);
                break;
            case 3:
                spawn(new PotionWA(), place.y, place.x);
                break;
            case 4:
                spawn(new PotionBD(), place.y, place.x);
                break;
            case 5:
                spawn(new PotionWD(), place.y, place.x);
                break;
        }
    }

    //spawning the gold piles
    if (hasBS) {
        int r = randomGen(0, 5);
        Pos place = chambers[r]->getSpawnPos();
        BarrierSuite *bs = new BarrierSuite();
        spawn(bs, place.y, place.x);
        for(int i = place.y - 1; i <= place.y + 1; i++) {
            bool b =false;
            for (int j = place.x - 1; j <= place.x + 1; j++) {
                if (theGrid[j][i] == Ground::empty && !(occupied[j][i])) {
                    b = true;
                    spawn(new Dragon(bs), i, j);
                    break;
                }
            }
            if (b) break;
        }
    }

    for (int i = 0; i < 10; i++) {
        int r = randomGen(0, 5);
        Pos place = chambers[r]->getSpawnPos();
        int type = randomGen(0, 8);

        switch(type) {
            case 0: case 1: case 2: case 3: case 4:
                spawn(new Gold(1), place.y, place.x);
                break;
            case 5: case 6:
                spawn(new Gold(2), place.y, place.x);
                break;
            case 7:
                DragonHoard *dh = new DragonHoard();
                spawn(dh, place.y, place.x);
                for(int i = place.y - 1; i <= place.y + 1; i++) {
                    bool b =false;
                    for (int j = place.x - 1; j <= place.x + 1; j++) {
                        if (theGrid[j][i] == Ground::empty && !(occupied[j][i])) {
                            b = true;
                            spawn(new Dragon(dh), i, j);
                            break;
                        }
                    }
                    if (b) break;
                }
                break;

        }
    }

}

void Floor::takeTurn() {
    for (auto c : living) {
        if (c) {
            c->move(0);
        }
    }
    notifyObservesrs();
    for (auto c : items) {
        if (c) {
            c->notifyObservesrs();
        }
    }
    for (auto c : living) {
        c->notifyObservesrs();
    }
}

void Floor::spawn(Creature *c, int posx, int posy) {
    occupied[posy][posx] = true;
    living.emplace_back(c);
    for (auto ob : observers) {
        (*c).attach(*ob);
    }
    c->setStartingPosition(posx, posy);
    c->setFloor(this);
    c->notifyObservesrs();
}

void Floor::spawn(PickUpable *what, int posx, int posy) {
    theGrid[posy][posx] = Ground::item;
    items.emplace_back(what);
    for(auto ob : observers) {
        (*what).attach(*ob);
    }

    what->recentX = posx;
    what->recentY = posy;
    what->notifyObservesrs();
}

void Floor::spawn(Potion *what, int posx, int posy) {
    theGrid[posy][posx] = Ground::potion;
    items.emplace_back(what);
    for(auto ob : observers) {
        (*what).attach(*ob);
    }
    what->recentX = posx;
    what->recentY = posy;
    what->fl = this;
    what->notifyObservesrs();
}

void Floor::spawnStairs() {
    Pos place = chambers[stairsCh]->getSpawnPos();
    spawn(new Stairs(), place.y, place.x);
}

void Floor::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}

Life *Floor::getPlayer() { return living[0]; }

Ground Floor::getState(int posx, int posy) {
    try {
        return theGrid[posy][posx];
    } catch (...) {
        return Ground::nothing;
    }
}


string Floor::getPlayerRace() { return PlayerRace; }

void Floor::gotMoved(int posx, int posy, Direction d) {
    occupied[posy][posx] = false;

    switch(d) {
        case Direction::N :
            occupied[posy - 1][posx] = true;
            break;
        case Direction::E :
            occupied[posy][posx + 1] = true;
            break;
        case Direction::S :
            occupied[posy + 1][posx] = true;
            break;
        case Direction::W :
            occupied[posy][posx - 1] = true;
            break;
        case Direction::NE :
            occupied[posy - 1][posx + 1] = true;
            break;
        case Direction::NW :
            occupied[posy - 1][posx - 1] = true;
            break;
        case Direction::SE :
            occupied[posy + 1][posx + 1] = true;
            break;
        case Direction::SW :
            occupied[posy + 1][posx - 1] = true;
            break;
        case Direction::Nothing:
            return;
    }

    recentX = posx;
    recentY = posy;
    notifyObservesrs();
}

Life *Floor::whatLife(int posx, int posy) {
    for (auto c : living) {
        if (c->getRecentX() == posx && c->getRecentY() == posy) {
            return c;
        }
    }
    return nullptr;
}


Item *Floor::whatItem(int posx, int posy) {
    for (auto i : items) {
        if (i->getRecentX() == posx && i->getRecentY() == posy) {
            return i;
        }
    }
    return nullptr;
}

void Floor::Interact(Player *who, Item *what) {
    who->beEffectedBy(what);
    int com = 0;
    for (auto it = living.begin(); it != living.end(); ++it) {
        if ((*it)->getCreature() == who) {
            com = what->effect(*it);
            break;
        }
    }

    if (com == 1) {
        spawnStairs();
    } else if (com == 2) {
        timeForNextFloor = true;
        return;
    }

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == what) {
            recentX = what->getRecentX();
            recentY = what->getRecentY();
            theGrid[recentY][recentX] = Ground::empty;
            notifyObservesrs();
            *it = nullptr;
            items.erase(it);
            delete what;
            break;
        }
    }
}



void Floor::replace(Life *what, Life *with) {
    for (auto it = living.begin(); it != living.end(); ++it) {
        if (*it == what) {
            *it = with;
            break;
        }
    }
}

int* minVal(int* cur, int* other){
    if (*cur > *other){
        return other;
    }
    return cur;
}

void Floor::initChambers() {
    if (chambers.size() != 0){
        for (auto ch : chambers) {
            delete ch;
        }
        chambers.clear();
    }
    vector<int*> labels = vector<int*>();
    vector<vector<int*>> tempMap = vector<vector<int*>>();
    chambers = vector<Chamber*>();
    int *offLabel = new int(200000);
    int inLabel = 0;
    int *tempPointer = new int(inLabel);
    for (int h = 0; h < heigth; h++){
        tempMap.emplace_back(vector<int*>());
        for (int i = 0; i < width; i++){
            if (theGrid[h][i] == Ground::empty || theGrid[h][i] == Ground::item || theGrid[h][i] == Ground::potion){
                if ((h == 0 && i == 0) ||
                        (!(h == 0 && i == 0) &&
                            ((h == 0 && *tempMap[h][i-1] == 200000) ||
                            (i == 0 && *tempMap[h-1][i] == 200000)))){
                    *tempPointer = inLabel;
                    tempMap[h].emplace_back(tempPointer);
                    labels.emplace_back(tempPointer);
                    inLabel++;
                }
                else {
                    *tempPointer = inLabel;
                    tempMap[h].emplace_back(tempPointer);
                    bool newPointer = true;
                    if (h != 0 && *tempMap[h - 1][i] < 200000) {
                        if (i != 0 && *tempMap[h - 1][i - 1] < 200000) {
                            newPointer = false;
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        if (*tempMap[h - 1][i] < 200000) {
                            newPointer = false;
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i]);
                        }
                        if (i != width - 1 && *tempMap[h - 1][i + 1] < 200000) {
                            newPointer = false;
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0 && *tempMap[h][i - 1] < 200000) {
                        newPointer = false;
                        tempMap[h][i] = minVal(tempMap[h][i - 1], tempMap[h][i - 1]);
                    }

                    if (newPointer){
                        inLabel++;
                        tempPointer = new int(inLabel);
                        labels.emplace_back(tempPointer);
                    }

                    if (h != 0 && *tempMap[h - 1][i] < 200000) {
                        if (i != 0 && *tempMap[h - 1][i - 1] < 200000) {
                            *tempMap[h - 1][i - 1] = *minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                            *tempMap[h][i] = *minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        if (*tempMap[h - 1][i] < 200000) {
                            *tempMap[h - 1][i] = *minVal(tempMap[h][i], tempMap[h - 1][i]);
                            *tempMap[h][i] = *minVal(tempMap[h][i], tempMap[h - 1][i]);
                        }
                        if (i != width - 1  && *tempMap[h - 1][i + 1] < 200000) {
                            *tempMap[h - 1][i + 1] = *minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                            *tempMap[h][i] = *minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0 && *tempMap[h][i - 1] < 200000) {
                        *tempMap[h][i - 1] = *minVal(tempMap[h][i], tempMap[h][i - 1]);
                        *tempMap[h][i] = *minVal(tempMap[h][i], tempMap[h][i - 1]);
                    }
                    inLabel++;
                }
            }
            else {
                tempMap[h].emplace_back(offLabel);
            }
        }
    }

    for (int h = 0; h < heigth; h++){
        for (int i = 0; i < width; i++){
            if (*tempMap[h][i] < 200000){
                bool isAdded = false;
                for (int j = 0; j < chambers.size(); j++){
                    if (*tempMap[h][i] == chambers[j]->getLabel()){
                        chambers[j]->addBlock(h, i, theGrid[h][i]);
                        isAdded = true;
                        break;
                    }
                }
                if (!isAdded){
                    Chamber *tempChamber = new Chamber(this, *tempMap[h][i]);
                    chambers.push_back(tempChamber);
                    chambers[chambers.size() - 1]->addBlock(h, i, theGrid[h][i]);
                }
            }
        }
    }
    delete offLabel;
    for (int h = 0; h < labels.size(); h++){
        delete labels[h];
    }
}

bool Floor::isOccupied(int posx, int posy) {
    if (posx < 0 || posy < 0 || posx >= width || posy >= heigth) {
        return false;
    }
    return occupied[posy][posx];
}

bool Floor::isPlayer(Life *who) {
    return (who == living[0]);
}

void Floor::died(Life *who) {
    for (auto it = living.begin(); it != living.end(); ++it) {
        if (*it == who) {
            occupied[who->getRecentY()][who->getRecentX()] = false;
            recentX = who->getRecentX();
            recentY = who->getRecentY();
            notifyObservesrs();
            *it = nullptr;
            living.erase(it);
            delete who;
            if (who == compassOwner) {
                Item *spawnedGold = whatItem(recentX, recentY);
                for (auto it = items.begin(); it != items.end(); ++it) {
                    if (*it == spawnedGold) {
                        recentX = spawnedGold->getRecentX();
                        recentY = spawnedGold->getRecentY();
                        theGrid[recentY][recentX] = Ground::empty;
                        notifyObservesrs();
                        *it = nullptr;
                        items.erase(it);
                        delete spawnedGold;
                        break;
                    }
                }
                spawn(new Compass(), recentX, recentY);
            }
            break;
            
        }
    }
}


Chamber::Chamber(Floor *owner, int label): label{label}, floor{owner}, blocks{std::vector<Block*>()}{}

Chamber::~Chamber() {

    for (int i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }

}

Chamber::Chamber(const Chamber &other): label(other.label), floor(other.floor), blocks(std::vector<Block*> {}) {
    for (auto bl : other.blocks) {
        Block *bl2 = new Block();
        bl2->pos = bl->pos;
        bl2->type = bl->type;
        blocks.emplace_back(bl2);
    }
}
void Chamber::addBlock(int h, int w, Ground type) {
    Pos pos;
    pos.x = h;
    pos.y = w;
    Block *block = new Block;
    block->pos = pos;
    block->type = type;
    blocks.emplace_back(block);
}

Pos Chamber::getSpawnPos() {
    int r = randomGen(0, blocks.size());

    while (blocks[r]->type != Ground::empty ||
           floor->getState(blocks[r]->pos.y, blocks[r]->pos.x) != Ground::empty ||
           floor->isOccupied(blocks[r]->pos.y, blocks[r]->pos.x)) {
        r = randomGen(0 , blocks.size());
    }

    return blocks[r]->pos;
}

int Chamber::getLabel(){
    return label;
}

void Chamber::setLabel(int label) {
    this->label = label;
}

void Floor::clearFloor() {
    for (auto c : living) {
        delete c;
    }
    living.clear();

    for (auto it : items) {
        delete it;
    }
    items.clear();
}

