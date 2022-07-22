//
// Created by kmajdi on 2022-07-14.
//
#include "floor.h"
#include "math.h"
#include "Enemy.h"
#include "randomGen.h"

Enemy::Enemy(int curHp, int atk, int def): Creature(curHp, atk, def, 0) {}

Enemy::~Enemy() { };

Direction directionOfCommand(int d, int *newX, int *newY) {
    switch (d) {
        case 0:
            *newY -= 1;
            return Direction::N;
        case 1:
            *newY += 1;
            return Direction::S;
        case 2:
            *newX += 1;
            return Direction::E;
        case 3:
            *newX -= 1;
            return Direction::W;
    }
}

void Enemy::move() {
    for (int i = recentX - 1; i <= recentX + 1 ;i++) {
        for (int j = recentY - 1; j <= recentY + 1; j++) {
            if (fl->isOccupied(i, j) && fl->isPlayer(fl->whatCreature(i, j))) {
                attack(fl->whatCreature(i, j), 0);
                return;
            }
        }
    }

    int command = randomGen(0, 4);
    int newX = recentX;
    int newY = recentY;
    Direction d = directionOfCommand(command, &newX, &newY);
    int count = 0;

    while((fl->getState(newX, newY) != Ground::empty && fl->getState(newX, newY) != Ground::path
           && fl->getState(newX, newY) != Ground::door) || fl->isOccupied(newX, newY)) {
        newX = recentX;
        newY = recentY;
        command = randomGen(0, 4);
        d = directionOfCommand(command, &newX, &newY);
        count++;

        if(count > 30) { return; }
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}

void Enemy::modifyHP(int amount)  {
    curHp += amount;
    if (curHp > maxHp) {
        curHp = maxHp;
    }
}

void Enemy::modifyGold(int amount) {
    gold += amount;
    if (gold < 0) {
        gold = 0;
    }
}



void Enemy::attack(Creature *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}


int Enemy::beAttackedBy(Creature *who, int defModifier) {

    def += defModifier;
    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    curHp -= damage;

    if (curHp <= 0) {
        // fear grows on me
        fl->died(this);
        return damage;
    }

    
    def -= defModifier;
    return damage;
}
