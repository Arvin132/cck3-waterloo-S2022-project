#include <string>
#include <iostream>
#include "floor.h"
#include "Subject.h"
#include "Observer.h"
#include "creature.h"
using namespace std;

Floor::Floor(std::istream &in, Player *p, Observer *intialOb): Subject(), theGrid(vector<vector<Ground>> {}),
                                           occupied(vector<vector<bool>> {}), living(vector<Creature*> {}) {
    observers.emplace_back(intialOb);
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
                    theGrid[j].emplace_back(Ground::nothing);
                    break;
            }
            occupied[j].emplace_back(false);

            recentX = i;
            recentY = j;
            notifyObservesrs();
        }
    }
    initChambers();
    cout << chambers.size();
    spawn(p, 10, 5);
}

Floor::~Floor() { }

void Floor::takeTurn() {
    for (auto c : living) {
        if (c) {
            c->move();
        }
    }
    notifyObservesrs();
    for (auto c : living) {
        c->notifyObservesrs();
    }
}

void Floor::spawn(Creature *c,int posx, int posy) {
    occupied[posy][posx] = true;
    living.emplace_back(c);
    for(auto ob : observers) {
        (*c).attach(ob);
    }
    c->setStartingPosition(posx, posy);
    c->setFloor(this);
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

Creature *Floor::whatCreature(int posx, int posy) {
    for (auto c : living) {
        if (c->getRecentX() == posx && c->getRecentY() == posy) {
            return c;
        }
    }
    return nullptr;
}

int* minVal(int* cur, int* other){
    if (*cur > *other){
        return other;
    }
    return cur;
}

void Floor::initChambers() {
    vector<vector<int*>> tempMap = vector<vector<int*>>();
    vector<int*> labels = vector<int*>();
    chambers = vector<Chamber>();
    int* offLabel = new int(200000);
    int inLabel = 0;
    for (int h = 0; h < heigth; h++){
        tempMap.emplace_back(vector<int*>());
        for (int i = 0; i < width; i++){
            if (theGrid[h][i] == Ground::empty || theGrid[h][i] == Ground::item){
                if ((h == 0 && i == 0) ||
                        (!(h == 0 && i == 0) &&
                            ((h == 0 && *tempMap[h][i-1] == 200000) ||
                            (i == 0 && *tempMap[h-1][i] == 200000)))){
                    tempMap[h].emplace_back(new int(inLabel));
                    inLabel++;
                }
                else {
                    tempMap[h].emplace_back(new int(inLabel));
                    if (h != 0 && *tempMap[h - 1][i] < 200000) {
                        if (i != 0 && *tempMap[h - 1][i - 1] < 200000) {
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        if (*tempMap[h - 1][i] < 200000) {
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i]);
                        }
                        if (i != width - 1 && *tempMap[h - 1][i + 1] < 200000) {
                            tempMap[h][i] = minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0 && *tempMap[h][i - 1] < 200000) {
                        tempMap[h][i] = minVal(tempMap[h][i - 1], tempMap[h][i - 1]);
                    }

                    if (h != 0 && *tempMap[h - 1][i] < 200000) {
                        if (i != 0 && *tempMap[h - 1][i - 1] < 200000) {
                            *tempMap[h - 1][i - 1] = *minVal(tempMap[h][i], tempMap[h - 1][i - 1]);
                        }
                        if (*tempMap[h - 1][i] < 200000) {
                            *tempMap[h - 1][i] = *minVal(tempMap[h][i], tempMap[h - 1][i]);
                        }
                        if (i != width - 1  && *tempMap[h - 1][i + 1] < 200000) {
                            *tempMap[h - 1][i + 1] = *minVal(tempMap[h][i], tempMap[h - 1][i + 1]);
                        }
                    }
                    if (i != 0 && *tempMap[h][i - 1] < 200000) {
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

    for (int h = 0; h < heigth; h++){
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
                    chambers.emplace_back(this, *tempMap[h][i]);
                }
            }
        }
    }
}

bool Floor::isOccupied(int posx, int posy) {
    if (posx < 0 || posy < 0 || posx >= width || posy >= heigth) {
        return false;
    }
    return occupied[posy][posx];
}

bool Floor::isPlayer(Creature *who) {
    return (who == living[0]);
}

void Floor::died(Creature *who) {
    for (auto it = living.begin(); it != living.end(); ++it) {
        if (*it == who) {
            occupied[who->getRecentY()][who->getRecentX()] = false;
            recentX = who->getRecentX();
            recentY = who->getRecentY();
            notifyObservesrs();
            *it = nullptr;
            living.erase(it);
            delete who;
            break;
        }
    }
}

Chamber::Chamber(Floor *owner, int label): floor{owner}, label{label}, blocks{std::vector<Block*>()}{}

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