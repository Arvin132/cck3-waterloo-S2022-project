//
// Created by kmajdi on 2022-07-14.
//
#include "floor.h"
#include "../creature.h"
#include "Enemy.h"

Enemy::~Enemy(int hp, int atk, int def): Creature(hp, atk, def, 0, false) { };

void Enemy::move() {
    char command = 'r';
    Direction d = Direction::E;

    int newX = recentX + 1;
    int newY = recentY;

    if (fl->getState(newX, newY) != Ground::empty || fl->getState(newX, newY) != Ground::path
        || fl->getState(newX, newY) != Ground::door) {
        char command = 'l';
        Direction d = Direction::W;
        int newX = recentX - 1;
        int newY = recentY;
    }

    
    fl->gotMoved(recentX, recentY, d);
    recentX = newX;
    recentY = newY;
}
