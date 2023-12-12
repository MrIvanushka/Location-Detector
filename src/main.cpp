#include<iostream>
#include<map>

#include "Satellite/Satellite.h"

typedef unsigned short SATELLITE_INDEX;
typedef double PSEUDODELAY;

int main()
{
	double estimationTime = 79103;
	std::map<SATELLITE_INDEX, std::pair<Satellite*, PSEUDODELAY>> satellites;

	//SAT 14
	Vector3 location(-16050.5732421875, 14867.69921875, 13161.53955078125);
	Vector3 velocity(1.122589111328125, -1.430501937866211, 2.971652984619141);
	Vector3 acceleration(-0.000000001862645, -0.000000000931323, 0);
	Clock clock(78300, -0.189058483e-6, 12.51604408e-6, 0.909e-12);

	satellites[14].first = new Satellite(location, velocity, acceleration, clock);
	satellites[14].second = 0.078468392917055;

	//SAT 4
	location = Vector3(-7976.09912109375, 10250.14208984375, 21974.18994140625);
	velocity = Vector3(-3.003422737121582, -0.023105621337891, -1.081212043762207);
	acceleration = Vector3(-0.000000001862645, -0.000000000931323, -0.000000000931323);
	Clock clock4(78300, -0.000000189058483, -0.000042061321437, 0.909e-12);

	satellites[4].first = new Satellite(location, velocity, acceleration, clock4);
	satellites[4].second = 0.073241217768673;


	//SAT 5
	location = Vector3(11406.8271484375, 10131.94384765625, 20440.77099609375);
	velocity = Vector3(-2.795928955078125, -0.131600379943848, 1.625444412231445);
	acceleration = Vector3(0, 0, -0.000000002793968);
	Clock clock5(78300, -0.000000189058483, 0.000169168226421, 0);

	satellites[5].first = new Satellite(location, velocity, acceleration, clock5);
	satellites[5].second = 0.063959853789407;


	//SAT 6
	location = Vector3(24342.75634765625, 3797.5458984375, 6671.1181640625);
	velocity = Vector3(-0.90982723236084, -0.160531044006348, 3.404714584350586);
	acceleration = Vector3(0.000000000931323, 0.000000000931323, -0.000000001862645);
	Clock clock6(78300, -0.000000189058483, -0.000032551586628, 0);

	satellites[6].first = new Satellite(location, velocity, acceleration, clock6);
	satellites[6].second = 0.070031111471884;

	//SAT 13
	location = Vector3(-11580.04296875, -855.91796875, 22690.44970703125);
	velocity = Vector3(1.662919998168945, -2.636009216308594, 0.747082710266113);
	acceleration = Vector3(-0.000000002793968, -0.000000000931323, -0.000000000931323);
	Clock clock13(78300, -0.000000189058483, 0.000401012599468, 0.909e-12);

	satellites[13].first = new Satellite(location, velocity, acceleration, clock13);
	satellites[13].second = 0.076208527072563;

	//SAT 19
	location = Vector3(12398.8369140625, 22230.0537109375, 1671.18994140625);
	velocity = Vector3(0.273331642150879, 0.116469383239746, -3.573365211486816);
	acceleration = Vector3(0.000000001862645, 0, -0.000000001862645);
	Clock clock19(78300, -0.000000189058483, 0.000065584667027, 0.909e-12);

	satellites[19].first = new Satellite(location, velocity, acceleration, clock19);
	satellites[19].second = 0.076981791669830;

	//SAT 20
	location = Vector3(14947.75830078125, 11321.74462890625, 17328.31982421875);
	velocity = Vector3(1.20386791229248, 2.046018600463867, -2.370450973510742);
	acceleration = Vector3(0, 0, -0.000000002793968);
	Clock clock20(78300, -0.000000189058483, 0.000058603473008, 0.909e-12);

	satellites[20].first = new Satellite(location, velocity, acceleration, clock20);
	satellites[20].second = 0.065272271294675;

	//SAT 21
	location = Vector3(10180.48388671875, -3836.06884765625, 23064.704589843750000);
	velocity = Vector3(1.483661651611328, 2.790823936462402, -0.199043273925781);
	acceleration = Vector3(0, 0, -0.000000001862645);
	Clock clock21(78300, -0.000000189058483, 0.000008144415915, 0.909e-12);

	satellites[21].first = new Satellite(location, velocity, acceleration, clock21);
	satellites[21].second = 0.066006480269953;

	//SAT 22
	location = Vector3(-344.43994140625, -18270.123046875, 17727.150390625);
	velocity = Vector3(1.049692153930664, 2.198596000671387, 0);
	acceleration = Vector3(-0.000000001862645, 0, -0.000000000931323);
	Clock clock22(78300, -0.000000189058483, -0.000092483125627, 0);

	satellites[22].first = new Satellite(location, velocity, acceleration, clock22);
	satellites[22].second = 0.078203448403038;

	std::cout << "===============SATELLITE COORDS================" << std::endl;

	for (const auto& pair : satellites)
	{
		SATELLITE_INDEX idx = pair.first;
		Satellite* sat = pair.second.first;
		PSEUDODELAY delay = pair.second.second;

		MotionParameters mp = sat->getMotionParameters(estimationTime, delay);

		std::cout << "Satellite " << idx << std::endl;
		std::cout << "	location: " << mp.location << std::endl;
		std::cout << "	velocity: " << mp.velocity << std::endl;
	}




	for (auto satellite : satellites)
		delete satellite.second.first;

	return 0;
}
