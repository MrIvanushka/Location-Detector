#ifndef MotionParameters_H
#define MotionParameters_H

#include "Vector3.h"

struct MotionParameters
{
	Vector3 location;
	Vector3 velocity;

	std::array<double, 6> toArray() const
	{
		std::array<double, 6> ret;

		ret[0] = location.x;
		ret[1] = location.y;
		ret[2] = location.z;
		ret[3] = velocity.x;
		ret[4] = velocity.y;
		ret[5] = velocity.z;

		return ret;
	}

	static MotionParameters fromArray(std::array<double, 6> arr)
	{
		MotionParameters mp;

		mp.location.x = arr[0];
		mp.location.y = arr[1];
		mp.location.z = arr[2];
		mp.velocity.x = arr[3];
		mp.velocity.y = arr[4];
		mp.velocity.z = arr[5];

		return mp;
	}
};

#endif