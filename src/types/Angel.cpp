#include "Angel.h"

#include <cmath>

namespace otg {

const double Angel::twoPi{ 2 * 3.14159265358979323846 };
const double Angel::permissibleVariation{ 0.01 };

Angel::Angel(double _a)
    : a{ std::fmod(_a, twoPi) }
{
}

Angel& Angel::operator+=(const Angel& rsh)
{
    a = std::fmod(a + rsh.a, twoPi);

    return *this;
}

Angel& Angel::operator-=(const Angel& rsh)
{
    a = std::fmod(a - rsh.a, twoPi);

    return *this;
}

Angel operator+(Angel lsh, const Angel& rsh)
{
    lsh += rsh;
    return lsh;
}

Angel operator-(Angel lsh, const Angel& rsh)
{
    lsh -= rsh;
    return lsh;
}

bool operator==(const Angel& lhs, const Angel& rhs)
{
    return std::abs(lhs.a - rhs.a) <= Angel::permissibleVariation;
}

std::string Angel::toString() const
{
    return "{" + std::to_string(a) + " rad }";
}

}  // namespace otg