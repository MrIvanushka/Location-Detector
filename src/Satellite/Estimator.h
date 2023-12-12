#ifndef Estimator_H
#define Estimator_H

#include <array>

class IEstimator
{
public:
	virtual void estimate(std::array<double, 6>& y, const std::array<double, 3>& rtt, double t_v) const = 0;
};

class RungeKutta : public IEstimator
{
private:
	double _timestamp;

public:
	RungeKutta(double timestamp = 1) : _timestamp(timestamp) {}

	void estimate(std::array<double, 6>& y, const std::array<double, 3>& rtt, double t_v) const override;

private:
	std::array<double, 6> estimateDiff(const std::array<double, 6>& k, const std::array<double, 3>& rtt) const;
};

#endif