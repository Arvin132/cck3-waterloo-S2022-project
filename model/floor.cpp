#include <iostream>
#include <string>
#include "floor.h"
#include "../observer/Subject.h"
#include "../observer/Observer.h"
#include "./creature/creature.h"
using namespace std;

Floor::Floor(std::istream &in): Subject(), theGrid(vector<vector<Ground>> {}),
                                occupied(vector<vector<bool>> {}), living(vector<Creature*> {}) {
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