#include "VelocityRotate.h"

namespace otg {

std::string VelocityRotate::toString() const
{
    return "{ d" + std::to_string(da.a) + " rad }";
}


}