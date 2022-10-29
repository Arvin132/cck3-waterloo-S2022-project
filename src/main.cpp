
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>
#include <memory>

using namespace std;

int main(int args, char *argv[]) {
	auto e = make_unique<EventHandler>(string {"cc3kfloor.txt"}, string {"welcome.txt"});
	e->initFloor();
	string input;
	while(!cin.fail()) {
		if (e->gameFinished()) {
			e->showScore();
			cout << "Would you like to (r)restart the game or (q) quit? " << endl;
			cin >> input;
			while(cin >> input && input.size() == 1 && string("qQrR").find(input[0]) < 0) {
				cout << "Please give valid input (r or q)" << endl;
			}

			if (input == "q" || input == "Q") {
				cout << "Thanks for playing our game :)" << endl;
				cout << "https://github.com/Arvin132 " << endl;
				cout << "https://github.com/kiarashmajdi " << endl;
				break;
			} else {
				e = make_unique<EventHandler>(string {"cc3kfloor.txt"}, string {"welcome.txt"});
				e->initFloor();
			}
		} 
		e->nextTurn();
	}
}
