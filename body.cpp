#include "body.h"
#include "cosmos.h"
#include "mathlib.h"


Body::Body(double x, double y, double mass, const Vector& accel) :
    Object(x, y, mass, accel)
{}

void Body::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    objs_t::iterator it;
    static Vector tmpa_;

    tmpa_.reset();

    while (it != pert_objs.end()) {
        tmpa_ += gravitation(*this, *it, cosmos.GConstant());
        ++it;
    }

    /* Newton's second law
     *    a = F/m
     */
    tmpa_ /= mass_;
    a_ += tmpa_;
}

