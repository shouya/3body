#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <vector>

#include "vector.h"

class Object;
class Cosmos;

typedef std::vector<Object> objs_t;

class Object {
public:
Object() : id_(0), x_(0), y_(0), a_(), mass_(0) {}
Object(double x, double y) : id_(0), x_(x), y_(y), a_(), mass_(0) {}
Object(double x, double y, double mass) :
    id_(0), x_(x), y_(y), a_(), mass_(mass) {}
Object(double x, double y, double mass, const Vector& accel):
    id_(0), x_(x), y_(y), a_(accel), mass_(mass) {}

protected:
    unsigned int id_;
    double x_, y_;
    Vector a_;
    double mass_;


public:
    unsigned int id(void) const { return id_; }
    void setId(unsigned int id) { id_ = id; }
    double mass(void) const { return mass_; }
    double x(void) const { return x_; } 
    double y(void) const { return y_; }
    const Vector& acceleration(void) const { return a_; }

public:
    virtual void move(void) {
        x_ += a_.x();
        y_ += a_.y();
    }

public:
    virtual void calcAccel(objs_t& pert_objs, const Cosmos& cosmos) {}
};


#endif /* __OBJECT_H__ */
