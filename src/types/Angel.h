#pragma once

#include <string>

namespace otg {

struct Angel
{
    explicit Angel(double _a = 0.0);

    double a;  // rad

    Angel& operator+=(const Angel& rsh);
    Angel& operator-=(const Angel& rsh);
    friend Angel operator+(Angel lsh, const Angel& rsh);
    friend Angel operator-(Angel lsh, const Angel& rsh);

    friend bool operator==(const Angel& lhs, const Angel& rhs);
    std::string toString() const;

    static const double twoPi;
    static const double permissibleVariation;
};

}  // namespace otg