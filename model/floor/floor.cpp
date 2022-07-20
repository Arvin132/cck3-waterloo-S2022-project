#include <string>
#include "floor.h"
#include "Subject.h"
#include "Observer.h"

using namespace std;

Floor::Floor(std::istream &in): Subject(), theGrid(vector<vector<Ground>> {}),
                                occupied(vector<vector<bool>> {}), living(vector<Creature*> {}) {
    char input = ' ';
    for (int j = 0; j < height; j++) {
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
                    theGrid[j].emplace_back(Ground::nothing);
                    break;
            }
            occupied[j].emplace_back(false);

            recentX = i;
            recentY = j;
            notifyObservesrs();
        }
    }
}

Floor::~Floor() { }

void Floor::takeTurn() {
    for (auto c : living) {
        c->move();
    }
    notifyObservesrs();
    for (auto c : living) {
        c->notifyObservesrs();
    }
}

void Floor::spawn(Creature *c,int posx, int posy) {
    occupied[posy][posx] = true;
    c->setStartingPosition(posx, posy);
    living.emplace_back(c);
    c->setFloor(this);
    for(auto ob : observers) {
        (*c).attach(ob);
    }
    c->notifyObservesrs();
}

void Floor::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}


Ground Floor::getState(int posx, int posy) {
    try {
        return theGrid[posy][posx];
    } catch (...) {
        return Ground::Vwall;
    }
}

void Floor::gotMoved(int posx, int posy, Direction d) {
    occupied[posy][posx] = false;
    switch(d) {
        case Direction::N :
            occupied[posy + 1][posx] = true;
        case Direction::E :
            occupied[posy][posx + 1] = true;
        case Direction::S :
            occupied[posy - 1][posx] = true;
        case Direction::W :
            occupied[posy][posx - 1] = true;

        recentX = posx;
        recentY = posy;
        notifyObservesrs();
    }

    
}


bool Floor::isOccupied(int posx, int posy) {
    return occupied[posy][posx];
}

int* minVal(int* cur, int* other){
    if (*cur > *other){
        return other;
    }
    return cur;
}

void Floor::initChambers() {
    vector<vector<int*>> tempMap  = vector<vector<int*>>();
    vector<int*> labels = vector<int*>();
    chambers = vector<Chamber>();
    int* offLabel = new int(200000);
    int inLabel = 0;
    for (int h = 0; h < height; h++){
        tempMap.emplace_back(vector<int*>());
        for (int i = 0; i < width; i++){
            if (theGrid[h][i] == empty || theGrid[h][i] == item){
                if ((h == 0 && i == 0)
                || (!(h == 0 && i == 0) && (
                        (h == 0 && *tempMap[h][i-1] == 200000)
                        || (i == 0 && *tempMap[h-1][i] == 200000)))){
                    tempMap[h].emplace_back(new int(inLabel));
                    inLabel++;
                }
                else {
                    tempMap[h].emplace_back(new int(inLabel));
                    if (h != 0 && *tempMap[h - 1][i] < 200000) {
                        if (i != 0 && *tempMap[h - 1][i - 1] < 200000) {
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i]);
                        if (i != width - 1) {
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0) {
                        tempMap[h][i] = minVal(tempMap[h][i - 1], tempMap[h][i - 1]);
                    }

                    if (h != 0) {
                        if (i != 0) {
                            *tempMap[h - 1][i - 1] = *minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        *tempMap[h - 1][i] = *minVal(tempMap[h][i], tempMap[h - 1][i]);
                        if (i != width - 1) {
                            *tempMap[h - 1][i + 1] = *minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0) {
                        *tempMap[h][i - 1] = *minVal(tempMap[h][i], tempMap[h][i - 1]);
                    }
                    inLabel++;
                }
            }
            else {
                tempMap[h].emplace_back(offLabel);
            }
        }
    }

    for (int h = 0; h < height; h++){
        for (int i = 0; i < width; i++){
            if (*tempMap[h][i] < 200000){
                bool isAdded = false;
                for (int j = 0; j < chambers.size(); j++){
                    if (*tempMap[h][i] == chambers[j].getLabel()){
                        chambers[j].addBlock(h, i, theGrid[h][i]);
                        isAdded = true;
                        break;
                    }
                }
                if (!isAdded){
                    Chamber curChamber(this);
                    curChamber.setLabel(*tempMap[h][i]);
                    chambers.emplace_back(this);
                }
            }
        }
    }
}

Chamber::Chamber(Floor *ownedBy): floor{ownedBy}, blocks{std::vector<Block*>()}{}

void Chamber::addBlock(int h, int w, Ground type) {
    Pos pos;
    pos.x = h;
    pos.y = w;
    Block *block = new Block;
    block->pos = pos;
    block->type = type;
    blocks.emplace_back(block);
}

int Chamber::getLabel(){
    return label;
}

void Chamber::setLabel(int label) {
    this->label = label;
}