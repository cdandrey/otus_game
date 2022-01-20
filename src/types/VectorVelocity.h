#pragma once

#include <string>

namespace otg {

struct VectorVelocity
{
    int dx = 0;
    int dy = 0;

    int sqrMovementLenght() const;

    VectorVelocity& operator+=(const VectorVelocity& rhs);
    VectorVelocity& operator-=(const VectorVelocity& rhs);
    friend VectorVelocity operator+(VectorVelocity lhs, const VectorVelocity& rhs);
    friend VectorVelocity operator-(VectorVelocity lhs, const VectorVelocity& rhs);
    friend bool operator==(const VectorVelocity& lhs, const VectorVelocity& rhs);
    std::string toString() const;
};

}  // namespace otg