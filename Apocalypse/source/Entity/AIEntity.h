#pragma once

#include <vector>
#include <random>

#include "Entity.h"

class AIEntity : public virtual Entity
{
protected:

	static const double EPSILON;
	static const std::vector<std::pair<int, int>> neighbors;
	static const std::vector<std::pair<int, int>> extendedNeighbors;
	static const std::vector<double> neighborsAngles;
	static const std::vector<double> extendedNeighborsAngles;

	double nearTargetRadius;

public:

	AIEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed);

	virtual void pathFindingTarget() = 0;
	virtual void onTargetReach() = 0;
	virtual bool nearTarget() = 0;

	static double random01();

	virtual ~AIEntity();
};

/*
const double AIEntity::EPSILON = 0.05;
const std::vector<std::pair<int, int>> AIEntity::neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
const std::vector<std::pair<int, int>> AIEntity::extendedNeighbors = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
const std::vector<double> AIEntity::neighborsAngles = {270.0, 90.0, 180.0, 0.0};
const std::vector<double> AIEntity::extendedNeighborsAngles = {225.0, 180.0, 135.0, 270.0, 90.0, 315.0, 0.0, 45.0};
*/