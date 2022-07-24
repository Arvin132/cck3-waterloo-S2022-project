
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>

using namespace std;

int main(int args, char *argv[]) {
	EventHandler *e;
	if (args == 1) {
		e = new EventHandler(string {"cc3kfloor.txt"}, string {"welcome.txt"}, true);
	} else if (args == 2) {
		e = new EventHandler(string {argv[1]}, string {"welcome.txt"}, true);
	} else {
		e = new EventHandler(string {argv[1]}, string {"welcome.txt"}, true);
	}

	e->initFloor();
	while(true) {
		if (e->gameFinished()) break;
		e->nextTurn();
	}

	delete e;
}
