#include "specialItem.h"
#include "life.h"
#include "floor.h"

DragonHoard::DragonHoard(): Gold(6) {}

BarrierSuite::BarrierSuite(): PickUpable() {
    rep = 'B';
    description = " has Picked up the Barrier Suite which halves the damage taken. ";
}

void BarrierSuite::effect(Life *who) {
    who->addBarrierSuite();
}

Stairs::Stairs(): PickUpable(){
    rep = '/';
}

void Stairs::effect(Life *who) {
}

Compass::Compass(): PickUpable() {
    rep = 'C';
}

void Compass::effect(Life *other) {
    fl->spawnStairs();
}
