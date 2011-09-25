#ifndef __MATHLIB_H__
#define __MATHLIB_H__

#include "vector.h"

#define PI 3.141592654

class Object;

double distance(const Object& obj1, const Object& obj2);
double direction(const Object& theObj, const Object& target);
Vector gravitation(const Object& theObj, const Object& target, double G);

void drawCircle(float x, float y, double radius,
                int r, int g, int b, int div_parts);

#endif /* __MATHLIB_H__ */
