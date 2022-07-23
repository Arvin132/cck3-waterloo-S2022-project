
//
// Created by kmajdi on 2022-07-14.
//

#include "EventHandler.h"
#include <string>

using namespace std;

int main(int args, char *argv[]) {
	EventHandler e(string {"cc3kfloor.txt"}, string {"welcome.txt"}, true);
	e.initFloor();
	while(true) {
		if (e.gameFinished()) break;
		e.nextTurn();
	}
}
