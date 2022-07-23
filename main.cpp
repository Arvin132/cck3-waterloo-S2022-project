
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>

using namespace std;

int main() {
	EventHandler e{};
	e.initFloor(string {"cc3kfloor.txt"});
	e.setup();
	while(true) {
		e.nextTurn();
		if (e.gameFinished()) break;
	}
}
