//
// Created by kmajdi on 2022-07-14.
//
#include "floor.h"
#include "Enemy.h"

Enemy::Enemy(int hp, int atk, int def): Creature(hp, atk, def, 0) {}

Enemy::~Enemy() { };

void Enemy::move() {
    Direction d = Direction::E;

    int newX = recentX + 1;

    if ((fl->getState(newX, recentY) != Ground::empty && fl->getState(newX, recentY) != Ground::path
        && fl->getState(newX, recentY) != Ground::door) || fl->isOccupied(newX, recentY)) {
        d = Direction::W;
        newX = recentX - 1;
    }

    if ((fl->getState(newX, recentY) != Ground::empty && fl->getState(newX, recentY) != Ground::path
        && fl->getState(newX, recentY) != Ground::door) || fl->isOccupied(newX, recentY)) {
        return ;
    }

    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
}

void Enemy::modifyHP(int amount)  {
    hp += amount;
}

void Enemy::modifyGold(int amount) {
    gold += amount;
}



void  Enemy::attack(Creature *other, int atkModifier) {}
void  Enemy::beAttackedBy(Creature *who, int defModifier) {}
