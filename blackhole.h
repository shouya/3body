#ifndef __BLACKHOLE_H__
#define __BLACKHOLE_H__

#include "object.h"

class BlackHole : public Object {
public:
    BlackHole(double x, double y, double mass);

    virtual void calcAccel(objs_t& pert_objs, const Cosmos& cosmos);
};

#endif /* __BLACKHOLE_H__ */
