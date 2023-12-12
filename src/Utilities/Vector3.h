#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <array>

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3() = default;

	Vector3(double X, double Y, double Z) : x(X), y(Y), z(Z) {}

	std::array<double, 3> toArray() const
	{
		std::array<double, 3> ret;

		ret[0] = x;
		ret[1] = y;
		ret[2] = z;

		return ret;
	}

	std::ostream& operator<<(std::ostream& os) {
		return os << '(' << x << "; " << y << "; " << z << ')';
	}
};

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	return os << '(' << v.x << "; " << v.y << "; " << v.z << ')';
}

#endif