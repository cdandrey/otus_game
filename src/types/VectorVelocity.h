#pragma once

#include "Point.h"

#include <string>

namespace otg {

struct VectorVelocity
{
    Point dp;
    std::string toString() const;
};

}  // namespace otg