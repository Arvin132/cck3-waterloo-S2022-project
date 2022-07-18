
//
// Created by kmajdi on 2022-07-14.
//

#include "eventHandler.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	EventHandler e{};
	e.initFloor(string {"cc3kfloor.txt"});
	e.setup();
	while(true) {
		e.nextTurn();
	}
}
