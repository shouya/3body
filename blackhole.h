#ifndef __BLACKHOLE_H__
#define __BLACKHOLE_H__

#include "object.h"

#define T_BLACKHOLE 3

class BlackHole : public Object {
public:
    BlackHole(const Vector& pos, double mass, double radius = 1);

    virtual void calcAccel(objs_t& pert_objs, const Cosmos& cosmos);
};

#endif /* __BLACKHOLE_H__ */
