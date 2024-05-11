#pragma once
#include "../Entity/Button/Button.h"
#include <iostream>
#include <vector>

class ButtonBuilder
{
public:
	static Button backButton(double x = 0, double y = 0);
	static void backButtonClickFunction(Button& button);

	static std::map<std::string, Button> WeaponCard(double x, double y, double width, double height, const std::string& id, int dmg, int firerate, int price, const std::string& weaponIconTextureName);

	static std::map<std::string, Button> ShopTabsButtons(double x, double y, double totalWidth, double totalHeight, const std::vector<std::string>& texturesWeapons, const std::vector<std::string>& texturesBullets, const std::vector<std::string>& texturesHealthArmor);

	static std::vector<std::vector<std::string>> tabTexturesWeaponsSelected();
	static std::vector<std::vector<std::string>> tabTexturesBulletsSelected();
	static std::vector<std::vector<std::string>> tabTexturesHealthArmorSelected();

	static std::map<std::string, Button> ShopTitleCard(double x, double y, double totalWidth, double totalHeight);

};