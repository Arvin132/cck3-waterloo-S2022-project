#include "textDisplay.h"
#include "floor.h"
#include "creature.h"
#include "item.h"
#include <vector>
#include <iostream>
using namespace std;

const std::string YELLOW =  "\033[33m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string RED = "\033[31m";
const std::string RESET =  "\033[0m";

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
        case Ground::nothing: case Ground::item: 
        case Ground::potion:
            display[j][i] = ' ';
            break;   
    }
}


std::ostream &operator<<(std::ostream &out, TextDisplay td) {
    for (int j = 0; j < td.heigth; j++) {
        for (int i = 0; i < td.width; i++) {
            string colour = RESET;
            switch (td.display[j][i]){            
                case 'N': case 'M': case 'V': case 'W':  
                case 'T': case 'X': case 'D':
                    colour = RED;
                    break;
                case 'G':
                    colour = YELLOW;
                    break;
                case 'P': case 'B':
                    colour = BLUE;
                    break;
                case '@': case '/': case 'C':
                    colour = GREEN;
                    break;
                default:
                    colour = RESET;
                    break;
            }
            out << colour << td.display[j][i] << RESET;
        }
        out << endl;
    }
    return out;
}
