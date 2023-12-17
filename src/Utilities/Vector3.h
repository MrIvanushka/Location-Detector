#ifndef VECTOR_3_H
#define VECTOR_3_H
#pragma once

#include <array>
#include <iomanip>
#include <iostream>

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

	Vector3 toGeodezic()
	{
		const double PI = 3.14159265358979323846;
		const double e = 0.006694379990141316996137335400448;
		const double a = 6378.137; // in km

		double d = sqrt(x * x + y * y);
		double b, l, h;

		if (d == 0)
		{
			b = PI * z / ( 2 * abs(z));
			h = z * sin(b) - sqrt(1 - (e * sin(b)) * (e * sin(b)));

			return Vector3(b, 0, h);
		}

		double la = abs(asin(y / d));

		if (y < 0 && x >= 0)
			l = 2 * PI - la;
		else if (y < 0 && x < 0)
			l = PI + la;
		else if (y > 0 && x < 0)
			l = PI - la;
		else if (y > 0 && x >= 0)
			l = la;
		else if (y == 0 && x > 0)
			l = 0;
		else //if (y == 0 && x < 0)
			l = PI;

		if (z == 0)
		{
			return Vector3(0, l, d - a);
		}

		double r = magnitude();
		double c = asin(z / r);
		double p = (e * e * a) / (2 * r);
		double tolerance = 4.85e-10;
		double s1 = 0;
		double s2 = 0;
		unsigned it = 0;

		do
		{
			s1 = s2;
			b = c + s1;
			s2 = asin(p * sin(2 * b)/sqrt(1 - (e * sin(b)) * (e * sin(b))));
			it++;
		}
		while (abs(s1 - s2) > tolerance);

		std::cout << "iterations: " << it << std::endl;

		h = d * cos(b) + z * sin(b) - a * sqrt(1 - (e * sin(b)) * (e * sin(b)));

		return Vector3(b, l, h);
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