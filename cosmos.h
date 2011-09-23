#ifndef __COSMOS_H__
#define __COSMOS_H__

#include <vector>

#include "object.h"
#include "painter.h"
#include "config.h"

typedef std::vector<Object*> objs_t;

class Cosmos {
    friend class Painter;
public:
    Cosmos(double G = g_config.gconst_,
           long rngx = g_config.xrng_, long rngy = g_config.yrng_);
    ~Cosmos(void);

public:


    void addObject(Object* object);
    void deleteObject(objs_t::iterator& obj_it);

    void calcAccel(void);
    void doMove(void);

    void mergeObjects(Object* o1, Object* o2);

    void loadFromConfig(void);

    int outOfRange(const Object* object) const;

    const objs_t& objects(void) const;
    const double GConstant(void) const;
    const int rangeX(void) const;
    const int rangeY(void) const;


public:
    static Object* createObject(int type, double x, double y,
                                double mass, double radius,
                                double ax, double ay);



private:
    objs_t objs_, nobjs_;
    const double G_;
    const long rngx_, rngy_;
};

#endif /* __COSMOS_H__ */
