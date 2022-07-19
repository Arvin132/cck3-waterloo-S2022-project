//
// Created by kmajdi on 2022-07-14.
//
#include <iostream>
#include "creature.h"
#include "player.h"
#include "floor.h"
#include <cmath>

Player::Player(std::istream *input, int hp, int atk, int def, int gold) : Creature(hp, atk, def, gold), input(input) {
    rep = '@';
}


void Player::attack(Creature *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}


void Player::beAttackedBy(Creature *who, int defModifier) {
    def += defModifier;

    int damage = ceil(100 / (100 + def) * who->getAtk());

    hp -= damage;

    if (hp <= 0) {
        // fear grows on me
        return fl->died(this);
    }
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
        case 'd':
            d = Direction::N;
            newY++;
            break;
        case 'u':
            d = Direction::S;
            newY -= 1;
            break;
        case 'r':
            d = Direction::E;
            newX++;
            break;
        case 'l':
            d = Direction::W;
            newX += -1;
            break;
    }

    if (fl->getState(newX, newY) != Ground::empty || fl->getState(newX, newY) != Ground::path
        || fl->getState(newX, newY) != Ground::door) {
        return move();
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