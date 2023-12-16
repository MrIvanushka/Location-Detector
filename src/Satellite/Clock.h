#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
	const unsigned SECONDS_IN_DAY = 86400;

public:
	const double startTime;
	const double gloToMdv;
	const double satToGlo;
	const double gamma;

	Clock() = default;

	Clock(double StartTime, double GloToMdv, double SatToGlo, double Gamma) : startTime(StartTime), gloToMdv(GloToMdv), satToGlo(SatToGlo), gamma(Gamma) {}

	double ethimeridicTime(double receiverTime, double delay) const
	{
		double tj = receiverTime - delay;
		double dt = gloToMdv + satToGlo - gamma * (tj - startTime);

		return clampTime(tj + dt);
	}

private:

	double clampTime(double time) const
	{
		if (time < 0)
			time += SECONDS_IN_DAY;
		else
			while (time > SECONDS_IN_DAY)
				time -= SECONDS_IN_DAY;

		return time;
	}
};

#endif