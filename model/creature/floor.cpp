#include <iostream>
#include <string>
#include <iomanip>
#include "floor.h"
#include "Observer.h"
#include "creature.h"
using namespace std;

Floor::Floor(std::istream &in): Subject(), theGrid(vector<vector<Ground>> {})
/*, living(vector<Creature> {})*/ {
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
                    break;
            }
        }
    }
}

Floor::~Floor() { }

void Floor::spawn(Creature &c) {
    living.emplace_back(c);
    for(auto ob : observers) {
        c.attach(ob);
    }
}

void Floor::notifyObservesrs() {
    for (auto i : observers) {
        i->notify(*this);
    }
}

bool Floor::validMove(int posx, int posy, Direction d) {
    try {
        switch(d) {
            case Direction::N:
                return (theGrid[posx][posy + 1] == Ground::empty) ? true : false;
            case Direction::E:
                return (theGrid[posx + 1][posy] == Ground::empty) ? true : false;
            case Direction::S:
                return (theGrid[posx][posy - 1] == Ground::empty) ? true : false;
            case Direction::W:
                return (theGrid[posx - 1][posy] == Ground::empty) ? true : false;
            default:
                return false;
        }
    } catch (out_of_range &e) {
        return false;
    }
}

Ground Floor::getState(int posx, int posy) {
    try {
        return theGrid[posy][posx];
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return Ground::empty;
    }
}