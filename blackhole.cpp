#include "blackhole.h"

BlackHole::BlackHole(double x, double y, double mass) :
    Object(x, y, mass)
{}

void BlackHole::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    /* black hole never do motion */
    return;
}
