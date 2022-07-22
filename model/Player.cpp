//
// Created by kmajdi on 2022-07-14.
//
#include <iostream>
#include "creature.h"
#include "player.h"
#include "floor.h"
#include <cmath>

Player::Player(std::istream *input, std::ostream *output, int hp, int atk, int def, int gold) : Creature(hp, atk, def, gold)
                                                                                                , input(input), output(output) {
    rep = '@';
}


void Player::attack(Creature *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}


void Player::beAttackedBy(Creature *who, int defModifier) {
    def += defModifier;

    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    curHp -= damage;
    std::cout << "got attacked for " << damage << " Damage" << std::endl;
    if (curHp <= 0) {
        // fear grows on me
        return fl->died(this);
    }

    def -= defModifier;
}

Direction whatDir(std::string command, int &newX, int &newY) {
    if (command == "no") {
        newY--;
        return Direction::N;
    } else if (command == "so") {
        newY++;
        return Direction::S;
    } else if (command == "ea") {
        newX++;
        return Direction::E;
    } else if (command == "we") {
        newX--;
        return Direction::W;
    } else if (command == "ne") {
        newX++;
        newY--;
        return Direction::NE;
    } else if (command == "nw") {
        newX--;
        newY--;
        return Direction::NW;
    } else if (command == "se") {
        newX++;
        newY++;
        return Direction::SE;
    } else if (command == "sw") {
        newX--;
        newY++;
        return Direction::SW;
    } else {
        return Direction::Nothing;
    }
}

void Player::move()  {
    std::string command = " ";
    *input >> command;
    Direction d = Direction::E;

    if (input->eof() || command == "q") {
        finished = true;
        return;
    }
    int newX = recentX;
    int newY = recentY;
    
    if (command == "a") {
        *input >> command;
        d = whatDir(command, newX, newY);

        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move();
        }

        if (fl->isOccupied(newX, newY)) {
            Creature *other = fl->whatCreature(newX, newY);
            attack(other, 0);
            return;
        } else {
            *output << "No creature in the specified position to attack " << std::endl;
            return move();
        }
    } else {
        d = whatDir(command, newX, newY);
        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move();
        }
    }
    
    if ((fl->getState(newX, newY) != Ground::empty && fl->getState(newX, newY) != Ground::path
        && fl->getState(newX, newY) != Ground::door) || fl->isOccupied(newX, newY)) {
        *output << "Invalid Move" << std::endl;
        return move();
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}


void Player::modifyHP(int amount)  {
    curHp += amount;
    if (curHp > maxHp) {
        curHp = maxHp;
    }
}

void Player::modifyGold(int amount) {
    gold += amount;
    if (gold < 0) {
        gold = 0;
    }
}

bool Player::isFinished() { return finished; }