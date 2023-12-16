#ifndef VECTOR_3_H
#define VECTOR_3_H
#pragma once

#include <array>
#include <iomanip>

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

	double magnitude() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3 operator + (Vector3 a)
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	Vector3 operator - (Vector3 a)
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
};

#endif