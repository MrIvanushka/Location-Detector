#ifndef RECORDER_SOLVER_H
#define RECORDER_SOLVER_H

#include <map>
#include <vector>

#include "Satellite/Satellite.h"

typedef unsigned short SATELLITE_INDEX;
typedef double PSEUDODELAY;

class Recorder
{
private:
	std::map<SATELLITE_INDEX, std::pair<Satellite*, PSEUDODELAY>> _satellites;

public:

	Recorder(std::map<SATELLITE_INDEX, std::pair<Satellite*, PSEUDODELAY>> satellites) : _satellites(satellites) {}

	Vector3 estimateLocation(double estimationTime, std::map<SATELLITE_INDEX, MotionParameters>* retSatellitesParams = nullptr);
};

#endif