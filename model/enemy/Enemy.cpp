//
// Created by kmajdi on 2022-07-14.
//
#include "floor.h"
#include "math.h"
#include "Enemy.h"

Enemy::Enemy(int hp, int atk, int def): Creature(hp, atk, def, 0) {}

Enemy::~Enemy() { };

void Enemy::move() {
    Direction d = Direction::E;

    int newX = recentX + 1;

    // if ((fl->getState(newX, recentY) != Ground::empty && fl->getState(newX, recentY) != Ground::path
    //     && fl->getState(newX, recentY) != Ground::door) || fl->isOccupied(newX, recentY)) {
    //     d = Direction::W;
    //     newX = recentX - 1;
    // }

    // if ((fl->getState(newX, recentY) != Ground::empty && fl->getState(newX, recentY) != Ground::path
    //     && fl->getState(newX, recentY) != Ground::door) || fl->isOccupied(newX, recentY)) {
    //     return ;
    // }

    

    // fl->gotMoved(recentX, recentY, d);
    // recentX = newX;
}

void Enemy::modifyHP(int amount)  {
    hp += amount;
}

void Enemy::modifyGold(int amount) {
    gold += amount;
}



void Enemy::attack(Creature *other, int atkModifier) {
    atk += atkModifier;
    other->beAttackedBy(this, 0);

    atk -= atkModifier;
}


void Enemy::beAttackedBy(Creature *who, int defModifier) {

    def += defModifier;
    double something = 100;
    int damage = ceil((something / (100 + def)) * who->getAtk());

    hp -= damage;
    std::cout << "got attacked and have hp left " << hp << std::endl;

    if (hp <= 0) {
        // fear grows on me
        return fl->died(this);
    }

    def -= defModifier;
}
