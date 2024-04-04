#include "blackhole.h"

BlackHole::BlackHole(const Vector& pos, double mass, double radius) :
    Object(T_BLACKHOLE, pos, mass, radius)
{}

void BlackHole::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    /* black hole never do motion */
    return;
}
