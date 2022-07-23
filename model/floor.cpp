#include <iostream>
#include <string>
#include <iomanip>
#include "floor.h"
#include "subject.h"
#include "observer.h"
#include "creature.h"
#include "gold.h"
#include "potion.h"

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
                case '0':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionRH(), i, j);
                    break;
                case '1':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionBA(), i, j);
                    break;
                case '2':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionBD(), i, j);
                    break;
                case '3':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionPH(), i, j);
                    break;
                case '4':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionWA(), i, j);
                    break;
                case '5':
                    theGrid[j].emplace_back(Ground::potion);
                    spawn(new PotionWD(), i, j);
                    break;
                case '6':
                    theGrid[j].emplace_back(Ground::gold);
                    spawn(new Gold(1), i ,j);
                    break;
                case '7':
                    theGrid[j].emplace_back(Ground::gold);
                    spawn(new Gold(2), i, j);
                    break;
                case '8':
                    theGrid[j].emplace_back(Ground::gold);
                    spawn(new Gold(4), i, j);
                    break;
                case '9':
                    theGrid[j].emplace_back(Ground::gold);
                    spawn(new Gold(6), i, j);
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

    spawn(p, 10, 5);
    for (auto it : items) {
        it->notifyObservesrs();
    }
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

void Floor::spawn(Gold *what, int posx, int posy) {
    theGrid[posy][posx] = Ground::gold;
    items.emplace_back(what);   
    for(auto ob : observers) {
        (*what).attach(ob);
    }

    what->recentX = posx;
    what->recentY = posy;
    what->notifyObservesrs();
}

void Floor::spawn(Potion *what, int posx, int posy) {
    theGrid[posy][posx] = Ground::potion;
    items.emplace_back(what);   
    for(auto ob : observers) {
        (*what).attach(ob);
    }
    what->recentX = posx;
    what->recentY = posy;
    what->fl = this;
    what->notifyObservesrs();
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

Item *Floor::whatItem(int posx, int posy) {
    for (auto i : items) {
        if (i->getRecentX() == posx && i->getRecentY() == posy) {
            return i;
        }
    }
    return nullptr;
}

void Floor::Interact(Player *who, Item *what) {
    what->effect(who);
    who->beEffectedBy(what);
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == what) {
            recentX = what->getRecentX();
            recentY = what->getRecentY();
            theGrid[recentY][recentX] = Ground::empty;
            notifyObservesrs();
            items.erase(it);
            delete what;
            break;
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

