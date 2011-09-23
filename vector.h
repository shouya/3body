#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>


class Vector {
public:
    Vector(void) : x_(0), y_(0) {}
    Vector(double x, double y) : x_(x), y_(y) {}

    Vector(const Vector& vec) : x_(vec.x_), y_(vec.y_) {}
    Vector& operator=(const Vector& vec) { return set(vec.x_, vec.y_); }

public:
    Vector& operator+=(const Vector& rhs) {
        x_+=rhs.x_; y_+=rhs.y_; return *this;
    }
    Vector& operator-=(const Vector& rhs) {
        x_-=rhs.x_; y_-=rhs.y_; return *this;
    }
    Vector& operator*=(double factor) {
        x_*=factor; y_*=factor; return *this;
    }
    Vector& operator/=(double divisor) {
        x_/=divisor;y_/=divisor;return *this;
    }
    Vector operator+(const Vector& rhs) const {
        Vector ret(*this); ret += rhs; return ret; }
    Vector operator-(const Vector& rhs) const {
        Vector ret(*this); ret -= rhs; return ret; }
    Vector operator*(double factor) const {
        Vector ret(*this); ret *= factor; return ret; }
    Vector operator/(double divisor) const {
        Vector ret(*this); ret /= divisor; return ret; }

public:
    double length(void) const { return sqrt(x_*x_ + y_*y_); }
#define PI 3.141592654

    double angle(void) const {
        if (x_ == 0) {
            return (y_>=0) ? (PI/2) : (3*PI/2);
        }
        double v = atan(y_/x_);
        if (x_ < 0) {
            return v + PI;
        }
        return v;
    }
#undef PI
    double x(void) const { return x_; }
    double y(void) const { return y_; }

public:
    Vector& set(double x, double y) {
        this->x_ = x; this->y_ = y;
        return *this;
    }
    Vector& setPolar(double length, double angle) {
/*        printf("l, a, [%f], [%f]\n", length, angle);*/
        x_ = cos(angle) * length;
        y_ = sin(angle) * length;
/*        printf("x,y, [%f, %f]\n", x_, y_);*/
        return *this;
    }
    void reset(void) {
        x_ = y_ = 0;
    }

public:
    static Vector fromPolar(double length, double angle) {
        return Vector().setPolar(length, angle);
    }
    static Vector fromRectangular(double x, double y) {
        return Vector(x, y);
    }

private:
    double x_, y_;
};

#endif /* __VECTOR_H__ */
