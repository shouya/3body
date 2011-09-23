#include "body.h"
#include "cosmos.h"
#include "mathlib.h"


Body::Body(double x, double y, double mass, const Vector& accel) :
    Object(x, y, mass, accel)
{}

void Body::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    objs_t::iterator it;
    static Vector tmpa;

    tmpa.reset();

    it = pert_objs.begin();
    while (it != pert_objs.end()) {
        if ((*it)->id() == id()) {
            ++it; continue;
        }
        tmpa += gravitation(*this, **it, cosmos.GConstant());
        ++it;
    }
/*        printf("%d x[%f], y[%f], m[%f], vx[%f], vy[%f], tvx[%f], tvy[%f]\n",
               id(), x(), y(), mass(),
               acceleration().x(),  acceleration().y(),
               tmpa_.x(), tmpa_.y());
*/
    

    /* Newton's second law
     *    a = F/m
     */
    tmpa /= mass_;
    a_ += tmpa;
}

