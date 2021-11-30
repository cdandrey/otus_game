#pragma once

#include <string>

namespace otg {

struct Vector
{
	int x = 0;
	int y = 0;
	int z = 0;

	Vector &operator+=(const Vector &rhs);
	Vector &operator-=(const Vector &rhs);
	friend Vector operator+(Vector lhs, const Vector &rhs);
	friend Vector operator-(Vector lhs, const Vector &rhs);
	friend bool operator==(const Vector &lhs, const Vector &rhs);
	std::string toString() const;
};

}  // namespace otg