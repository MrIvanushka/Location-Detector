#include "RecorderSolver.h"
#include "Slae/densematrix.h"
#include "Slae/overloads.h"

const double LIGHTSPEED = 299792.458;

Vector3 Recorder::estimateLocation(double estimationTime, std::map<SATELLITE_INDEX, MotionParameters>* retSatellitesParams)
{
	std::vector<MotionParameters> satellitesParams;

	Vector3 recorderLocation(0,0,0);
	double recorderTime = 0;

	int currentRow = 0;
	std::vector<double> Sigma(_satellites.size());

	for (const auto& pair : _satellites)
	{
		SATELLITE_INDEX idx = pair.first;
		Satellite* sat = pair.second.first;
		PSEUDODELAY delay = pair.second.second;

		auto currentParams = sat->getMotionParameters(estimationTime, delay);
		satellitesParams.push_back(currentParams);

		if (retSatellitesParams)
			(*retSatellitesParams)[idx] = currentParams;

		Sigma[currentRow] = LIGHTSPEED * (estimationTime - sat->clock().ethimeridicTime(estimationTime, delay));

		currentRow++;
	}

	double tolerance = 0.001;
	Vector3 delta;
	
	do
	{
		std::vector<double> currentSigma = Sigma;
		
		DenseMatrix<double> H(_satellites.size(), 4);
		std::vector<double> D(_satellites.size());

		for (auto currentRow = 0u; currentRow < currentSigma.size(); currentRow++)
		{
			D[currentRow] = (recorderLocation - satellitesParams[currentRow].location).magnitude();

			H(currentRow, 0) = (recorderLocation.x - satellitesParams[currentRow].location.x);
			H(currentRow, 1) = (recorderLocation.y - satellitesParams[currentRow].location.y);
			H(currentRow, 2) = (recorderLocation.z - satellitesParams[currentRow].location.z);
			H(currentRow, 3) = 1;
			
			currentSigma[currentRow] -= (D[currentRow] + recorderTime);
		}
		auto transposedH = H.transpose();

		auto theta = (transposedH * H).inverse() * transposedH * currentSigma;
		delta = Vector3(theta[0], theta[1], theta[2]);

		recorderLocation = recorderLocation + delta;
		recorderTime += theta[3];
	} 
	while (delta.magnitude() > tolerance);
	
	return recorderLocation;
}