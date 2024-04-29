#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"
#include "../InteractiveEntity.h"

class Door : public virtual CollidableEntity, public virtual AnimatedEntity, public virtual InteractiveEntity
{
private:

	bool interactUsed;

	void interact();
	void interactReleased();

protected:
	int openCost;

public:
	Door(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string> animationsName2D, double interactionWidth, double interactionHeight, int openCost);
	virtual ~Door() = default;

	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;

	void setupPlayerInputComponent();

	bool isInInteraction() override;
	void onInteraction() override;

	void update() override;
};

