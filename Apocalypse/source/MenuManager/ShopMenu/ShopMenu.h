#pragma once

#include "../../ButtonGroup/ButtonGroup.h"
#include "../MenuBase/MenuBase.h"
#include "../../ButtonBuilder/ButtonBuilder.h"


// Abstract shop menu

class ShopMenuAbstract : public virtual MenuBase
{
protected:
	double buttonOffsetX = 50;
	double buttonOffsetY = 50;
	double spaceAfterButton = 20;

	ButtonGroup buttons;

protected:
	ShopMenuAbstract(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	virtual ~ShopMenuAbstract() = default;
	// ShopMenuAbstract(const ShopMenuAbstract& other) = default;
	// ShopMenuAbstract& operator=(const ShopMenuAbstract& other) = default;
	// ShopMenuAbstract(const ShopMenuAbstract&& other) = default;
	// ShopMenuAbstract& operator=(const ShopMenuAbstract&& other) = default;

	virtual std::map<std::string, Button> loadMenuItems() = 0;

public:
	void draw();

	void setupInputComponent() override;
	void playMenu() override;

	virtual double getCardPosX();
	virtual double getCardPosY(int index);
};





// Weapons tab

class ShopMenuWeapons : public virtual ShopMenuAbstract
{
private:

private:
	ShopMenuWeapons(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	virtual ~ShopMenuWeapons() = default;
	ShopMenuWeapons(const ShopMenuWeapons& other) = delete;
	ShopMenuWeapons& operator=(const ShopMenuWeapons& other) = delete;
	ShopMenuWeapons(const ShopMenuWeapons&& other) = delete;
	ShopMenuWeapons& operator=(const ShopMenuWeapons&& other) = delete;

	virtual std::map<std::string, Button> loadMenuItems() override;

public:
	static ShopMenuAbstract& get();
};





// Bullets tab

class ShopMenuBullets : public virtual ShopMenuAbstract
{
private:

private:
	ShopMenuBullets(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	virtual ~ShopMenuBullets() = default;
	ShopMenuBullets(const ShopMenuBullets& other) = delete;
	ShopMenuBullets& operator=(const ShopMenuBullets& other) = delete;
	ShopMenuBullets(const ShopMenuBullets&& other) = delete;
	ShopMenuBullets& operator=(const ShopMenuBullets&& other) = delete;

	virtual std::map<std::string, Button> loadMenuItems() override;

public:
	static ShopMenuAbstract& get();
};





// Health/Armor tab

class ShopMenuHealthArmor : public virtual ShopMenuAbstract
{
private:

private:
	ShopMenuHealthArmor(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	virtual ~ShopMenuHealthArmor() = default;
	ShopMenuHealthArmor(const ShopMenuHealthArmor& other) = delete;
	ShopMenuHealthArmor& operator=(const ShopMenuHealthArmor& other) = delete;
	ShopMenuHealthArmor(const ShopMenuHealthArmor&& other) = delete;
	ShopMenuHealthArmor& operator=(const ShopMenuHealthArmor&& other) = delete;

	virtual std::map<std::string, Button> loadMenuItems() override;

public:
	static ShopMenuAbstract& get();
};