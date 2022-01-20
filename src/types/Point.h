#pragma once

#include <string>

namespace otg {

struct VectorVelocity;

struct Point
{
    int x = 0;
    int y = 0;

    Point& operator+=(const VectorVelocity& vec);
    Point& operator-=(const VectorVelocity& vec);
    friend Point operator+(Point pnt, const VectorVelocity& vec);
    friend Point operator-(Point pnt, const VectorVelocity& vec);

    Point& operator+=(const Point& rhs);
    Point& operator-=(const Point& rhs);
    friend Point operator+(Point lhs, const Point& rhs);
    friend Point operator-(Point lhs, const Point& rhs);

    friend bool operator==(const Point& lhs, const Point& rhs);
    std::string toString() const;
};

}  // namespace otg