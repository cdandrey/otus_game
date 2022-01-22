#include "Point.h"

namespace otg {

Point& Point::operator+=(const Point& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Point& Point::operator-=(const Point& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Point operator+(Point lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;
}

Point operator-(Point lhs, const Point& rhs)
{
    lhs -= rhs;
    return lhs;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::string Point::toString() const
{
    return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
}

}  // namespace otg