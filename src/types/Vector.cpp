#include "Vector.h"

namespace otg {

Vector& Vector::operator+=(const Vector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

Vector operator+(Vector lhs,const Vector &rhs)
{
    lhs += rhs;
    return lhs;
}

bool operator== (const Vector& lhs,const Vector& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

std::string Vector::toString() const
{
    return "{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "}";
}

}