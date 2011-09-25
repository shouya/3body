#include <cmath>

#include <GL/gl.h>

#include "mathlib.h"
#include "object.h"

#define PI 3.141592654

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

/*    printf("the [%d]->[%d](%f,%f)\t", theObj.id(), target.id(),
      target.x()-theObj.x(), target.y()-theObj.y());*/
    force = G * theObj.mass() * target.mass();
    dist = distance(theObj, target);
    if (dist != 0) {
        force /= pow(dist, 2);
/*        printf("dist: [%f]\t", dist);*/
    } else {
        force *= 99999999; /* time a very big number instead divide by zero */
    }
    direct = direction(theObj, target);
/*    printf ("direct: %f\n", direct * 180/PI);*/
    return Vector::fromPolar(force, direct);
}



void drawCircle(float x, float y, double radius,
                int r, int g, int b, int div_parts) {
    int i = 0;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(r, g, b);
    glVertex2f(x, y);
    for (; i != div_parts + 1; ++i) {
        glVertex2f(x + radius*cos(2*PI/div_parts * i),
                   y + radius*sin(2*PI/div_parts * i));
    }
    glEnd();
}

#undef PI

