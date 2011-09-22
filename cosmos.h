#ifndef __COSMOS_H__
#define __COSMOS_H__

#include <vector>

#include "object.h"
#include "painter.h"

class Cosmos {
    friend class Painter;
public:
    Cosmos(void);
    Cosmos(double G);
    ~Cosmos(void);

public:
    void addObject(const Object& object);
    void calcAccel(void);
    void doMove(void);
    const objs_t& objects(void) const;

    const double GConstant(void) const;

private:
    objs_t objs_;
    const double G_;
};

#endif /* __COSMOS_H__ */
