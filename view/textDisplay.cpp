#include "textDisplay.h"
#include "floor.h"
#include "creature.h"
#include "item.h"

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

char TextDisplay::welcomeScreen(istream &input) {
    string s;
    while(!input.fail()) {
        getline(input, s);
        cout << s << endl;
    }
    char race;
    
    while(cin >> race) {
        switch(race) {
            case 'H': case 'h':
                return 'h';
            case 'o': case 'O':
                return 'o';
            case 'd': case 'D':
                return 'd';
            case 'E': case 'e':
                return 'e';
            default:
                cout << "please give valid input" << endl;
                continue;
        }
    }

    return '\0';
}

void TextDisplay::notify(Creature &who) {
    display[who.getRecentY()][who.getRecentX()] = who.getRep();
}

void TextDisplay::notify(Item &who) {
    display[who.getRecentY()][who.getRecentX()] = who.getRep();
}


void TextDisplay::notify(Floor &who) {
    int i = who.getRecentX();
    int j = who.getRecentY();
    Ground state = who.getState(i, j);
    switch (state) {
        case Ground::empty:
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
        case Ground::nothing: case Ground::gold: 
        case Ground::potion:
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
