#include "VectorVelocity.h"

namespace otg {

std::string VectorVelocity::toString() const
{
    return "{d" + std::to_string(dp.x) + ", d" + std::to_string(dp.y) + "}";
}

}  // namespace otg