//
// Created by kmajdi on 2022-07-14.
//
#include <iostream>
#include "creature.h"
#include "player.h"
#include "item/item.h"
#include "floor.h"
#include <cmath>
#include "randomGen.h"

Player::Player(std::istream *input, std::ostream *output, bool *gameFinished,
               int hp, int atk, int def, int gold) : Creature(hp, atk, def, gold), input(input), output(output), gameFinished(gameFinished) {
    rep = '@';
}

Player::Player(const Player &other):Creature(other.maxHp, other.atk, other.def, other.gold), input(other.input)
                                    , output(other.output), gameFinished(other.gameFinished) {
    observers.clear();
}

void Player::attack(Life *other, int atkMod) {
    atk += atkMod;
    char rep = other->getRep();
    std::string damage = std::to_string(other->beAttackedBy(this, 0));
    log = log + ("PC attacked and dealt " + damage + " Damage to " + std::string{rep} + ". ");
    atk -= atkMod;
}


int Player::beAttackedBy(Life *who, int defModifier) {
    def += defModifier;
    int r = randomGen(0, 2);
    int damage = 0;
    if (r == 0) {
        double something = 100;
        damage = ceil((something / (100 + def)) * who->getAtk());
        if (hasBarrierSuite) {
            damage /= 2;
        }
        std::string damageStr = std::to_string(damage);
        log = log + (std::string{who->getRep()} + " attacked and dealt " + damageStr + " Damage to PC. ");
        curHp -= damage;
    } else if (r == 1) {
        log = log + (std::string{who->getRep()} + " attacked but missed. ");
    }

    if (curHp <= 0) {
        // fear grows on me
        *gameFinished = true;
        return damage;
    }
    
    def -= defModifier;
    return damage;
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

void Player::move(int atkMod)  {
    std::string command = " ";
    *input >> command;
    Direction d = Direction::E;

    if (command == "q") {
        *gameFinished = true;
        return;
    }

    if (input->fail()) {
        return;
    }
    int newX = recentX;
    int newY = recentY;
    
    if (command == "a") {
        *input >> command;
        d = whatDir(command, newX, newY);

        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move(atkMod);
        }

        if (fl->isOccupied(newX, newY)) {
            Life *other = fl->whatLife(newX, newY);
            attack(other, atkMod);
            return;
        } else {
            *output << "No creature in the specified position to attack " << std::endl;
            return move(atkMod);
        }



    } else if (command == "u") {
        *input >> command;
        d = whatDir(command, newX, newY);

        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move(atkMod);
        }

        if (fl->getState(newX, newY) == Ground::potion) {
            Item *what = fl->whatItem(newX, newY);
            fl->Interact(this, what);
            return;
        } else {
            *output << "No Potion is in that Direction for you to consume " << std::endl;
            return move(atkMod);
        }



    } else if (command == "v") {
        *input >> command;
        d = whatDir(command, newX, newY);

        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move(atkMod);
        }

        if (fl->isOccupied(newX, newY)) {
            Life *what = fl->whatLife(newX, newY);
            *output << "Player sees" << what->getInfo() << std::endl;
            return move(atkMod);
        } else if (fl->getState(newX, newY) == Ground::potion || fl->getState(newX, newY) == Ground::item) {
            Item *what = fl->whatItem(newX, newY);
            *output << "Player sees" << what->getInfo() << std::endl;
            return move(atkMod);
        } else if (fl->getState(newX, newY) == Ground::Hwall || fl->getState(newX, newY) == Ground::Vwall || fl->getState(newX, newY) == Ground::nothing) {
            *output << "Player sees a Wall" << std::endl;
            return move(atkMod);
        } else if (fl->getState(newX, newY) == Ground::door) {
            *output << "Player sees a Door" << std::endl;
            return move(atkMod);
        } else { 
            *output << "Player sees empty Ground" << std::endl;
            return move(atkMod);
        }



    } else {
        d = whatDir(command, newX, newY);
        if (d == Direction::Nothing) {
            *output << "Please Give valid input" << std::endl;
            return move(atkMod);
        }
    }
    
    if ((fl->getState(newX, newY) != Ground::empty && fl->getState(newX, newY) != Ground::path
        && fl->getState(newX, newY) != Ground::door && fl->getState(newX, newY) != Ground::item) || fl->isOccupied(newX, newY)) {
        *output << "Invalid Move" << std::endl;
        return move(atkMod);
    }

    

    if (fl->getState(newX, newY) == Ground::item) {
        Item *it = fl->whatItem(newX, newY);
        if (it->hasPermisson()) {
            fl->Interact(this, it);
        } else {
            *output << "Something is not letting you pick up the item" << std::endl;
            return move(atkMod);
        }
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
    if (command != "a") {
        for (int i = recentX - 1; i <= recentX + 1 ;i++) {
            for (int j = recentY - 1; j <= recentY + 1; j++) {
                if (fl->isOccupied(i, j) && (i != recentX || j != recentY)) {
                    attack(fl->whatLife(i, j), atkMod);
                    return;
                }
            }
        }
    }
}

void Player::addBarrierSuite() {
    hasBarrierSuite = true;
}

std::string Player::getInfo() {
    return " the PC.";
}

bool Player::hasBarrierEffect() {
    return hasBarrierSuite;
}

void Player::beEffectedBy(Item *what) {
    log += "PC" + what->getDescription();
}

std::string Player::report() { 
    std::string retVal = log;
    log.clear();
    return retVal;
}

