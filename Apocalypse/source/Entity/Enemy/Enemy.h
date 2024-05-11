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
	std::pair<int, int> lastChosenCell;

	std::pair<int, int> chosenCell;
	int chosenCellIndex;

	double rotateSpeed;

	double probToChangeDir;

public:

	Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double health, double rotateSpeed);
	~Enemy();

	virtual void pathFindingTarget() override;
	virtual void onTargetReach() override;
	virtual bool nearTarget() override;

	virtual void update() override;
};