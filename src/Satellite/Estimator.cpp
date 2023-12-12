#include "Estimator.h"

void RungeKutta::estimate(std::array<double, 6>& y, const std::array<double, 3>& rtt, double t_v) const
{
		double time = 0;
		double timestamp = _timestamp;

		std::array<double, 6> K;
		std::array<double, 6> dy;
		std::array<double, 6> y_mod;

		for (auto currentIter = 1u; time < t_v; currentIter++)
		{
			unsigned stepsCount = 4;

			for (auto i = 0u; i < stepsCount; i++)
			{
				std::array<double, 6> arr;

				if (i == 0)
					arr = estimateDiff(y, rtt);
				else
					arr = estimateDiff(y_mod, rtt);

				for (auto j = 0u; j < 6; j++)
				{
					K[j] = timestamp * arr[j];

					if (i == 0)
						dy[j] = K[j];
					else if (i == stepsCount - 1)
						dy[j] += K[j];
					else
						dy[j] += K[j] * 2;

					y_mod[j] = y[j] + dy[j] / 2;
				}
			}

			for (auto i = 0u; i < 6; i++)
			{
				y[i] += dy[i] / 6.0;
			}
			time += timestamp;

			if ((time + timestamp) > t_v)
			{
				timestamp = t_v - time;
			}
		}
}


std::array<double, 6> RungeKutta::estimateDiff(const std::array<double, 6>& k, const std::array<double, 3>& rtt) const
{
		std::array<double, 6> arr;

		double A1 = 6378.136;
		double mu = 398600.44;
		double c20 = -1082.63e-6;
		double wz = 0.7292115e-4;

		double ae2 = pow(A1, 2);
		double w2 = pow(wz, 2);
		double r = sqrt(pow(k[0], 2) + pow(k[1], 2) + pow(k[2], 2));
		double r2 = pow(r, 2);
		double r3 = pow(r, 3);
		double r5 = pow(r, 5);
		double c1 = 3 * c20 * mu * ae2 / (2 * r5);
		double c2 = (-1) * mu / r3;
		double c3 = (5 * pow(k[2], 2) / r2);

		arr[0] = k[3];
		arr[1] = k[4];
		arr[2] = k[5];
		arr[3] = c2 * k[0] + c1 * k[0] * (1 - c3) + w2 * k[0] + 2 * wz * k[4] + rtt[0];
		arr[4] = c2 * k[1] + c1 * k[1] * (1 - c3) + w2 * k[1] - 2 * wz * k[3] + rtt[1];
		arr[5] = c2 * k[2] + c1 * k[2] * (3 - c3) + rtt[2];

		return arr;
}