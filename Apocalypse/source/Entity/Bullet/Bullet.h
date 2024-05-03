#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"

#include <glm/glm.hpp>

class Bullet : public virtual CollidableEntity, public virtual TexturableEntity
{
protected:
	double damage;

public:
	Bullet(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double damage);
	virtual ~Bullet() = default;

	virtual void onCollide(CollidableEntity& other, glm::vec2 overlap) override;
	void update() override;
};

