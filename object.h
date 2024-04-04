#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <vector>

#include "vector.h"
#include "cosmos.h"

class Object;
class Cosmos;

typedef std::vector<Object*> objs_t;

#define T_OBJECT 0


class Object {
    friend class Cosmos;
public:
    explicit Object(int type) : type_(type), id_(0), p_(), v_(),
        a_(), mass_(0), r_(0), to_del_(0) {}
    Object(int type, const Vector& pos) : type_(type), id_(0),
        p_(pos), v_(), a_(), mass_(0), r_(0), to_del_(0) {}
    Object(int type, const Vector& pos, double mass, double radius) :
        type_(type), id_(0), p_(pos), a_(), mass_(mass), r_(radius), to_del_() {}
    Object(int type, const Vector& pos, double mass, double radius,
           const Vector& vel, const Vector& accel):
        type_(type), id_(0), p_(pos), v_(vel), a_(accel),
        mass_(mass), r_(radius), to_del_() {}

    virtual ~Object(void) {};

protected:
    int type_;
    unsigned int id_;
    Vector p_;
    Vector v_; /* velocity */
    Vector a_; /* accelerate */
    double mass_;
    double r_; /* radius */
    int to_del_;

public:
    unsigned int id(void) const { return id_; }
    void setId(unsigned int id) { id_ = id; }
    double mass(void) const { return mass_; }
    double x(void) const { return p_.x(); }
    double y(void) const { return p_.y(); }
    double radius(void) const { return r_; }
    int type(void) const { return type_; }
    int isDead(void) const { return (to_del_ != 0); }

    const Vector& velocity(void) const { return v_; }
    Vector& velocity(void) { return v_; }

    const Vector& acceleration(void) const { return a_; }
    Vector& acceleration(void) { return a_; }

public:
    virtual void move(float dt) {
        v_ += a_ * dt;
        p_ += v_ * dt;
    }

public:
    virtual void calcAccel(objs_t& pert_objs, const Cosmos& cosmos) = 0;
};


#endif /* __OBJECT_H__ */
