#include "VectorVelocity.h"

namespace otg {

int VectorVelocity::sqrMovementLenght() const
{
    return (dx * dx) + (dy * dy);
}

VectorVelocity& VectorVelocity::operator+=(const VectorVelocity& rhs)
{
    dx += rhs.dx;
    dy += rhs.dy;

    return *this;
}

VectorVelocity& VectorVelocity::operator-=(const VectorVelocity& rhs)
{
    dx -= rhs.dx;
    dy -= rhs.dy;

    return *this;
}

VectorVelocity operator+(VectorVelocity lhs, const VectorVelocity& rhs)
{
    lhs += rhs;
    return lhs;
}

VectorVelocity operator-(VectorVelocity lhs, const VectorVelocity& rhs)
{
    lhs -= rhs;
    return lhs;
}

bool operator==(const VectorVelocity& lhs, const VectorVelocity& rhs)
{
    return (lhs.dx == rhs.dx) && (lhs.dy == rhs.dy);
}

std::string VectorVelocity::toString() const
{
    return "{d" + std::to_string(dx) + ", d" + std::to_string(dy) + "}";
}

}  // namespace otg