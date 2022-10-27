
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>

using namespace std;

int main(int args, char *argv[]) {
	EventHandler *e;
	e = new EventHandler(string {"cc3kfloor.txt"}, string {"welcome.txt"});
	e->initFloor();
	while(!cin.fail()) {
		if (e->gameFinished()) {
			e->showScore();
			break;
		} 
		e->nextTurn();
	}

	delete e;
}
