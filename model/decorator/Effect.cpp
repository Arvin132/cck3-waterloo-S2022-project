//
// Created by kmajdi on 2022-07-14.
//

#include "effect.h"

ModAtk::ModAtk(Life *next,int amount): Decorator(next), mod(amount) {}

void ModAtk::move(int atkMod) { next->move(atkMod + mod); }

int ModAtk::beAttackedBy(Life *who, int defModifier) { return next->beAttackedBy(who, defModifier); }

int ModAtk::getAtk() { return next->getAtk() + mod; }
int ModAtk::getDef() { return next->getDef(); }

ModDef::ModDef(Life *next,int amount): Decorator(next), mod(amount) {}


void ModDef::move(int atkMod) { next->move(atkMod); }

int ModDef::beAttackedBy(Life *who, int defModifier) { return next->beAttackedBy(who, defModifier + mod); }

int ModDef::getAtk() { return next->getAtk(); }
int ModDef::getDef() { return next->getDef() + mod; }