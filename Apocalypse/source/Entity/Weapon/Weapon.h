#pragma once

#include <string>

#include "../../GlobalClock/GlobalClock.h"
#include "../PickUp/PickUp.h"

class Weapon : public virtual PickUp
{
public:
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

protected:
	double fireRate;
	int numBullets;
	double damage;
	double reloadTime;

	double timeSinceLastShot;
	double timeSinceStartReload;

	WeaponType weaponType;

	double shortRangeAttackRadius;

public:
	Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D, double interactionWidth, double interactionHeight, double fireRate, int numBullets, double damage, double reloadTime, WeaponType weaponType, double shortRangeAttackRadius);
	virtual ~Weapon() = default;

	virtual bool isInInteraction() override;
	virtual void onInteraction() override;

	inline WeaponType getWeaponType() const { return this->weaponType; }

	virtual void onClick();

	inline bool stillReloading() const { return GlobalClock::get().getCurrentTime() - this->timeSinceLastShot < this->reloadTime; }

	virtual void update() override;

	void drawWeapon();
};

