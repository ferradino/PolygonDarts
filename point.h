#include "fraction.h"

#ifndef _POINT_H
#define _POINT_H

class Point {
    private:
        Fraction
            xCord,
            yCord;

    public:
        Point (Fraction _xCord = 0, Fraction _yCord = 0);
        ~Point() = default;

        Point operator+(Point rhs);
        Point operator-(Point rhs);
        Fraction operator*(Point rhs);
        Point operator*(Fraction rhs);

        bool operator==(Point rhs);
        bool operator!=(Point rhs);

        Fraction getXCord() { return xCord; }
        Fraction getYCord() { return yCord; }
};

std::istream &operator>>(std::istream &is, Point &p);
std::ostream &operator<<(std::ostream &os, Point p);

#endif
