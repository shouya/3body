#include "cosmos.h"

#include <stdio.h>

/* gravitational constant */
Cosmos::Cosmos(double G, long rngx, long rngy) :
    objs_(), G_(G), rngx_(rngx), rngy_(rngy) {}

Cosmos::~Cosmos(void) {
    while (!objs_.empty()) {
        delete objs_.back();
        objs_.pop_back();
    }
}

void Cosmos::addObject(Object* object) {
    static unsigned int obj_id = 0;
    objs_.push_back(object);
    objs_.back()->setId(obj_id++);
}

void Cosmos::doMove(void) {
    objs_t::iterator it = objs_.begin();

    while (it != objs_.end()) {
        (*it)->calcAccel(objs_, *this);
        ++it;
    }
    it = objs_.begin();
    while (it != objs_.end()) {      
        (*it)->move();

        if (outOfRange(*it)) {
            delete (*it);
            it = objs_.erase(it);
            continue;
        }
        ++it;
    }
}
int Cosmos::outOfRange(const Object* object) const {
    double x = object->x(),
        y = object->y();

    if (x < -rngx_ || x >= rngx_ ||
        y < -rngy_ || y >= rngy_) {
        printf("object[%d] dead(out of range), (%f,%f)\n", object->id(), x, y);
        return 1;
    }
    return 0;
}


const objs_t& Cosmos::objects(void) const {
    return objs_;
}

const double Cosmos::GConstant(void) const {
    return G_;
}

const int Cosmos::rangeX(void) const {
    return rngx_;
}

const int Cosmos::rangeY(void) const {
    return rngy_;
}


