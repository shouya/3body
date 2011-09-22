#include "cosmos.h"

/* gravitational constant */
Cosmos::Cosmos(void) : objs_(), G_(6.67e-11) {}
Cosmos::Cosmos(double G) : objs_(), G_(G) {};
Cosmos::~Cosmos(void) {}

void Cosmos::addObject(const Object& object) {
    static unsigned int obj_id = 0;
    objs_.push_back(object);
    objs_.back().setId(obj_id++);
}

void Cosmos::doMove(void) {
    objs_t::iterator it = objs_.begin();

    while (it != objs_.end()) {
        it->calcAccel(objs_, *this);
        ++it;
    }
    it = objs_.begin();
    while (it != objs_.end()) {
        it->move();
        ++it;
    }
}

const objs_t& Cosmos::objects(void) const {
    return objs_;
}

const double Cosmos::GConstant(void) const {
    return G_;
}
