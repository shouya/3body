#include "mathlib.h"
#include "object.h"

double distance(const Object& obj1, const Object& obj2) {
    return sqrt(pow(obj1.x()-obj2.x(), 2) + pow(obj1.y()-obj2.y(), 2));
}

double direction(const Object& theObj, const Object& target) {
    return Vector(target.x()-theObj.x(), target.y()-theObj.y()).angle();
}

Vector gravitation(const Object& theObj, const Object& target, double G) {
    double force;
    double dist;
    double direct;
    /* The law of universal gravitation
     *       m1 m2
     * F = G-------
     *        r^2
     */
    force = G * theObj.mass() * target.mass();
    dist = distance(theObj, target);
    if (dist != 0) {
        force /= pow(dist, 2);
    } else {
        force *= 99999999; /* time a very big number instead divide by zero */
    }
    direct = direction(theObj, target);
    return Vector::fromPolar(force, direct);
}

