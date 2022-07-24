#include "specialItem.h"
#include "life.h"
#include "floor.h"

BarrierSuite::BarrierSuite(): PickUpable() {
    rep = 'B';
}

void BarrierSuite::effect(Life *who) {
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
