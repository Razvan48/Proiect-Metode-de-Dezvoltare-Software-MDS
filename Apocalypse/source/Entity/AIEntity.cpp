#include "AIEntity.h"

const double AIEntity::EPSILON = 0.05;
const double AIEntity::EPSILON_ANGLE = 7.5;
const std::vector<std::pair<int, int>> AIEntity::neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
const std::vector<std::pair<int, int>> AIEntity::extendedNeighbors = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
const std::vector<double> AIEntity::neighborsAngles = { 270.0, 90.0, 180.0, 0.0 };
const std::vector<double> AIEntity::extendedNeighborsAngles = { 225.0, 180.0, 135.0, 270.0, 90.0, 315.0, 0.0, 45.0 };

AIEntity::AIEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed)
	: Entity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	, nearTargetRadius(3.0) // TODO: schimbam valoarea
{

}

double AIEntity::random01()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}

AIEntity::~AIEntity()
{

}

