#pragma once

#include <vector>
#include <queue>

#include "../Human/Human.h"
#include "../AIEntity.h"

class Enemy : public virtual Human, public virtual AIEntity
{
protected:

	std::vector<std::vector<bool>> blockedCell;
	std::vector<std::vector<int>> cellDistance;
	std::queue<std::pair<int, int>> q;
	std::vector<std::pair<int, int>> visitedCells;

	double rotateSpeed;

	double probToChangeDir;

	std::pair<double, double> currentTarget;
	std::pair<double, double> nextTarget;

public:

	Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double health, double rotateSpeed);
	~Enemy();

	virtual void pathFindingTarget() override;
	virtual void onTargetReach() override;
	virtual bool nearTarget() override;

	virtual void update() override;
};