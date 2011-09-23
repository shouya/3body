#include "blackhole.h"

BlackHole::BlackHole(double x, double y, double mass, double radius) :
    Object(T_BLACKHOLE, x, y, mass, radius)
{}

void BlackHole::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    /* black hole never do motion */
    return;
}
