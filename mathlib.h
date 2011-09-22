#ifndef __MATHLIB_H__
#define __MATHLIB_H__

#include "vector.h"

class Object;

double distance(const Object& obj1, const Object& obj2);
double direction(const Object& theObj, const Object& target);
Vector gravitation(const Object& theObj, const Object& target, double G);

#endif /* __MATHLIB_H__ */
