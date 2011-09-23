#ifndef __COSMOS_H__
#define __COSMOS_H__

#include <vector>

#include "object.h"
#include "painter.h"

class Cosmos {
    friend class Painter;
public:
    Cosmos(double G = 6.67e-7,
           long rngx = 1e3, long rngy = 1e3);
    ~Cosmos(void);

public:
    void addObject(Object* object);
    void calcAccel(void);
    void doMove(void);
    int outOfRange(const Object* object) const;

    const objs_t& objects(void) const;
    const double GConstant(void) const;
    const int rangeX(void) const;
    const int rangeY(void) const;

private:
    objs_t objs_;
    const double G_;
    const long rngx_, rngy_;
};

#endif /* __COSMOS_H__ */
