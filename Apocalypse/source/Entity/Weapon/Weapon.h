#pragma once

#include <string>

#include "../PickUp/PickUp.h"

class Weapon : public virtual PickUp
{
protected:

	double fireRate;
	int numBullets;
	double damage;
	double reloadTime;

	double timeSinceLastShot;
	double timeSinceStartReload;

	static enum class WeaponType
	{
		FIST,
		KNIFE,
		PISTOL,
		SHOTGUN,
		AK47,
		M4,
		MINIGUN
	};

	WeaponType weaponType;

	double shortRangeAttackRadius;

public:

	Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D, double interactionWidth, double interactionHeight, double fireRate, int numBullets, double damage, double reloadTime, WeaponType weaponType, double shortRangeAttackRadius);

	virtual bool isInInteraction() override;
	virtual void onInteraction() override;

	virtual void onClick();

	virtual ~Weapon();
};

