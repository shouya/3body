#include <cstdio>
#include <cmath>

#include "cosmos.h"
#include "config.h"
#include "mathlib.h"

#include "body.h"
#include "blackhole.h"


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
                             double ax, double ay) {
    switch (type) {
    case T_BODY:
        return new Body(x, y, mass, radius, Vector(ax, ay));
    case T_BLACKHOLE:
        return new BlackHole(x, y, mass, radius);
    default:;
    }

    return NULL;
}


void Cosmos::doMove(void) {
    objs_t::iterator it = objs_.begin(), it2;

    while (it != objs_.end()) {
        (*it)->calcAccel(objs_, *this);
        ++it;
    }
    it = objs_.begin();
    for (; it != objs_.end(); ++it) {
        if ((*it)->to_del_ == 1) continue;

        (*it)->move();

        if (outOfRange(*it)) {
            printf("object[%d] dead(OOR), (%f,%f)\n",
                   (*it)->id_, (*it)->x_, (*it)->y_);
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
    double m1 = o1->mass_,
        m2 = o2->mass_;

    double new_x = m1 < m2 ? o2->x_ : o1->x_,
        new_y = m1 < m2 ? o2->y_ : o1->y_;
    double new_ax = (o1->a_.x() * m1 + o2->a_.x() * m2) / (m1+m2),
        new_ay = (o2->a_.x() * m1 + o2->a_.y() * m2) / (m1+m2);
    double new_m = m1 + m2;
    double new_r = sqrt(o1->r_*o1->r_ + o2->r_*o2->r_);
    int new_type =
        (((o1->type_|o2->type_) == (T_BODY|T_BODY)) ? T_BODY :
         ((o1->type_|o2->type_) == (T_BODY|T_BLACKHOLE)) ? T_BLACKHOLE :
         (/* two blackholes, merge them to one */T_BLACKHOLE));
    

    /* solute accel speed too big as follow way, not a beatiful implement */
    new_ax = new_ay = 0;

    nobjs_.push_back(Cosmos::createObject(new_type, new_x, new_y,
                                          new_m, new_r, new_ax, new_ay));

    o1->to_del_ = o2->to_del_ = 1;
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


