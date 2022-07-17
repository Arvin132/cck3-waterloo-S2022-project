//
// Created by kmajdi on 2022-07-14.
//
#include <iostream>
#include "creature.h"
#include "player.h"
#include "floor.h"

Player::Player(std::istream *input, int hp, int atk, int def, int gold) : Creature(hp, atk, def, gold), input(input) {
    rep = '@';
}


void Player::attack(Creature *other, int atkModifier) {

}


void Player::beAttackedBy(Creature *who, int defModifier) {

}
void Player::move()  {
    char command = ' ';
    *input >> command;
    Direction d = Direction::E;

    if (command != 'u' && command != 'r'
        && command != 'd' && command != 'l') {
            return move();
    }

    int newX = recentX;
    int newY = recentY;

    switch (command) {
        case 'u':
            d = Direction::N;
            newX++;
            break;
        case 'd':
            d = Direction::S;
            newX -= 1;
            break;
        case 'r':
            d = Direction::E;
            newY++;
            break;
        case 'l':
            d = Direction::W;
            newY += -1;
            break;
    }

    if (fl->getState(newX, newY) != Ground::empty) {
        move();
        return;
    }

    
    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}
void Player::modifyHP(int amount)  {
    hp += amount;
}

void Player::modifyGold(int amount) {
    gold += amount;
}