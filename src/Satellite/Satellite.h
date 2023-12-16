#ifndef SATELLITE_H
#define SATELLITE_H

#include<memory>

#include "../Utilities/MotionParameters.h"
#include "Estimator.h"
#include "Clock.h"

class Satellite
{
private:
	MotionParameters	_startMotionParameters;
	Vector3				_startAcceleration;
	double				_startTime;
	Clock				_clock;
	IEstimator*			_estimator;
public:

	Satellite(Vector3 r, Vector3 v, Vector3 w,	Clock clock) : _startAcceleration(w), _clock(clock)
	{
		_startMotionParameters.location = r;
		_startMotionParameters.velocity = v;
		_estimator = new RungeKutta();
	}

	Satellite(Vector3 r, Vector3 v, Vector3 w, Clock clock, IEstimator* estimator) : _startAcceleration(w), _clock(clock), _estimator(estimator) {
		_startMotionParameters.location = r;
		_startMotionParameters.velocity = v;
	}

	const Clock& clock()
	{
		return _clock;
	}

	MotionParameters getMotionParameters(double receiverTime, double delay) const
	{
		double t_v = _clock.ethimeridicTime(receiverTime, delay) - _clock.startTime;

		std::array<double, 6> y = _startMotionParameters.toArray();
		std::array<double, 3> rtt = _startAcceleration.toArray();

		_estimator->estimate(y, rtt, t_v);

		return MotionParameters::fromArray(y);
	}
};

#endif