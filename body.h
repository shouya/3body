#ifndef __BODY_H__
#define __BODY_H__

#include "object.h"
#include "vector.h"

#define T_BODY 1

class Body : public Object {
public:
    Body(double x, double y, double mass, double radius,
         const Vector& accel = Vector());

    virtual void calcAccel(objs_t& pert_objs, const Cosmos& cosmos);
};

#endif /* __BODY_H__ */
