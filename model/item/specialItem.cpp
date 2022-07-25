#include "specialItem.h"
#include "life.h"
#include "floor.h"

DragonHoard::DragonHoard(): Gold(6) {}

BarrierSuite::BarrierSuite(): PickUpable() {
    rep = 'B';
    description = " has Picked up the Barrier Suite which halves the damage taken. ";
}

int BarrierSuite::effect(Life *who) {
    who->addBarrierSuite();
    return 0;
}

Stairs::Stairs(): PickUpable(){
    rep = '/';
}

int Stairs::effect(Life *who) {
    return 2;
}

Compass::Compass(): PickUpable() {
    rep = 'C';
    description = " has Picked up the Compass and revealed the location of Stairs";
}

int Compass::effect(Life *other) {
    return 1;
}
