#include <cstdio>
#include <cmath>

#include "cosmos.h"
#include "config.h"
#include "mathlib.h"

#include "body.h"
#include "blackhole.h"
#include "misc.h"


/* gravitational constant */
Cosmos::Cosmos(double G, long rngx, long rngy) :
    objs_(), nobjs_(), G_(G), rngx_(rngx), rngy_(rngy) {}

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

void Cosmos::deleteObject(objs_t::iterator& obj_it) {
    delete (*obj_it);
    *obj_it = NULL;
    obj_it = objs_.erase(obj_it);
}

Object* Cosmos::createObject(int type, double x, double y,
                             double mass, double radius,
                             double vx, double vy,
                             double ax, double ay) {
    switch (type) {
    case T_BODY:
        return new Body(Vector(x, y), mass, radius, Vector(vx, vy), Vector(ax, ay));
    case T_BLACKHOLE:
        return new BlackHole(Vector(x, y), mass, radius);
    default:;
    }

    return NULL;
}


void Cosmos::doMove(float dt) {
    objs_t::iterator it = objs_.begin(), it2;

    while (it != objs_.end()) {
        (*it)->calcAccel(objs_, *this);
        ++it;
    }
    it = objs_.begin();
    for (; it != objs_.end(); ++it) {
        if ((*it)->to_del_ == 1) continue;

        (*it)->move(dt);

        if (outOfRange(*it)) {
            printf("object[%d] dead(OOR), (%f,%f)\n",
                   (*it)->id_, (*it)->x(), (*it)->y());
            (*it)->to_del_ = 1;
            continue;
        }

        if (!g_config.merge_mode_) {
            continue;
        }

        for (it2 = it+1; it2 != objs_.end(); ++it2) {
            if (!(*it && *it2)) continue;
            if (distance(**it, **it2) < (*it)->r_ + (*it2)->r_) {
                mergeObjects(*it, *it2);
                break;
            }
        } /* for merge objs */
    } /* for all objs, do; */

    it = objs_.begin();
    while (it != objs_.end()) {
        if ((*it)->to_del_) {
            deleteObject(it);
            if (it == objs_.end()) {
                break;
            }
        }
        ++it;
    }

    while (!nobjs_.empty()) {
        addObject(nobjs_.back());
        nobjs_.pop_back();
    }

} /* end function void doMove(void) */


void Cosmos::mergeObjects(Object* o1, Object* o2) {
    /* make o1 the heavier one or blackhole */
    if (o2->type_ == T_BLACKHOLE) {
        if (o1->type_ == T_BLACKHOLE) {
            if (o1->mass_ < o2->mass_) {
                swap(o1, o2);
            }
        } else {
            swap(o1, o2);
        }
    } else if (o1->mass_ < o2->mass_) {
        swap(o1, o2);
    }

    o1->a_.set(0, 0);
    o1->mass_ = o1->mass_ + o2->mass_;
    o1->r_ = sqrt(pow(o1->r_,2) + pow(o2->r_,2));

    o2->to_del_ = 1;
}



void Cosmos::loadFromConfig(void) {
    while (!g_config.objs_.empty()) {
        addObject(g_config.objs_.back());
        g_config.objs_.pop_back();
    }
}


int Cosmos::outOfRange(const Object* object) const {
    double x = object->x(),
        y = object->y();

    if (x < -rngx_ || x >= rngx_ ||
        y < -rngy_ || y >= rngy_) {
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
