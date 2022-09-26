#include "point.h"

Point::Point(Fraction _xCord, Fraction _yCord) {
    xCord = _xCord,
    yCord = _yCord;

}

Point Point::operator+(Point rhs) {
    Fraction
        newX, newY;

    newX = xCord + rhs.xCord;
    newY = yCord + rhs.yCord;

    return Point(newX, newY);
}

Point Point::operator-(Point rhs) {
    Fraction
        newX, newY;

    newX = xCord - rhs.xCord;
    newY = yCord - rhs.yCord;

    return Point(newX, newY);
}

Fraction Point::operator*(Point rhs) {
    return xCord * rhs.yCord - yCord * rhs.xCord;
}

Point Point::operator*(Fraction scale) {
    Fraction
        newX, newY;

    newX = xCord * scale;
    newY = yCord * scale;

    return Point(newX, newY);
}

bool Point::operator==(Point rhs) {
    return xCord == rhs.xCord && yCord == rhs.yCord;
}

bool Point::operator!=(Point rhs) {
    return xCord != rhs.xCord || yCord != rhs.yCord;
}

std::istream &operator>>(std::istream &is, Point &p) {
    Fraction
        x,y;

    char
        comma,
        leftParenthesis,
        rightParenthesis;

    is >> leftParenthesis >> x >> comma >> y >> rightParenthesis;

    p = Point(x, y);

    return is;
}

std::ostream &operator<<(std::ostream &os, Point p){
    os << '(' << p.getXCord() << ',' << p.getYCord() << ')';

    return os;
}
