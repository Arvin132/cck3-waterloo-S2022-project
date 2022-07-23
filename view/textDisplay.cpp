#include "textDisplay.h"
#include "../model/floor.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(): Observer(), display(vector<vector<char>> {}) {
    for (int j = 0; j < heigth; j++) {
        display.emplace_back(vector<char> {});
        for (int i = 0; i < width; i++) {
            display[j].emplace_back(' ');
        }
    }
}

void TextDisplay::notify(Creature &who) {
    display[who.getRecentY()][who.getRecentX()] = who.getRep();
}

void TextDisplay::notify(Floor &who) {
    int i = who.getRecentX();
    int j = who.getRecentY();
    Ground state = who.getState(i, j);
    switch (state) {
        case Ground::empty: case Ground::item:
            display[j][i] = '.';
            break;
        case Ground::Vwall:
            display[j][i] = '|';
            break;
        case Ground::Hwall:
            display[j][i] = '-';
            break;
        case Ground::path:
            display[j][i] = '#';
            break;
        case Ground::door:
            display[j][i] = '+';
            break;
        case Ground::nothing:
            display[j][i] = ' ';
            break;
        
    }
}


std::ostream &operator<<(std::ostream &out, TextDisplay td) {
    for (int j = 0; j < td.heigth; j++) {
        for (int i = 0; i < td.width; i++) {
            out << td.display[j][i];
        }
        out << endl;
    }
    return out;
}
