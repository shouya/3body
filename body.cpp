#include "body.h"
#include "cosmos.h"
#include "mathlib.h"


Body::Body(double x, double y, double mass, double radius,
           const Vector& accel) :
    Object(T_BODY, x, y, mass, radius, accel)
{}

void Body::calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {
    objs_t::iterator it;
    static Vector tmpa;

    tmpa.reset();

    it = pert_objs.begin();
    while (it != pert_objs.end()) {
        /*   is self            or  was dead */
        if ((*it)->id() == id() || (*it)->isDead()) {
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
    if (mass_) {
        tmpa /= mass_;
    } else {
        tmpa /= INFINITESIMAL;
    }
    a_ += tmpa;
}

