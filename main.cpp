
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>

using namespace std;

int main(int args, char *argv[]) {
	EventHandler e{};
	e.initFloor(string {"cc3kfloor.txt"}, string {"welcome.txt"});
	e.setup();
	while(true) {
		if (e.gameFinished()) break;
		e.nextTurn();
	}
}
