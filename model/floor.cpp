#include <iostream>
#include <string>
#include <iomanip>
#include "floor.h"
#include "subject.h"
#include "observer.h"
#include "creature.h"
using namespace std;

Floor::Floor(std::istream &in, Observer *initialOb): Subject(), theGrid(vector<vector<Ground>> {}),
                                                    living(vector<Creature*> {}) {
    attach(initialOb);
    char input = ' ';
    for (int j = 0; j < heigth; j++) {
        theGrid.emplace_back(vector<Ground> {});
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
    switch(d) {
        case Direction::N :
            theGrid[posy + 1][posx] = Ground::occupied;
        case Direction::E :
            theGrid[posy][posx + 1] = Ground::occupied;
        case Direction::S :
            theGrid[posy - 1][posx] = Ground::occupied;
        case Direction::W :
            theGrid[posy][posx - 1] = Ground::occupied;

        recentX = posx;
        recentY = posy;
        notifyObservesrs();
    }

    
}