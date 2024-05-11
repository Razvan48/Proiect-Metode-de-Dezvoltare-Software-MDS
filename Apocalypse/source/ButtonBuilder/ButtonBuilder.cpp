#include "ButtonBuilder.h"

#include <algorithm>
#include <exception>

#include "../ResourceManager/ResourceManager.h"
#include "../MenuManager/MenuManager.h"
#include "../Renderer/TextRenderer.h"


Button ButtonBuilder::backButton(double x, double y)
{
	return Button(x, y, 40, 40, 0, 0, 40, 40, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, "back"}, { Button::Status::HOVERED, "backHovered" }, { Button::Status::CLICKED, "backHovered" }}, "");
}

void ButtonBuilder::backButtonClickFunction(Button& button) {
	MenuManager::get().top().setIsInMenu(false);
	MenuManager::get().pop();
}


std::map<std::string, Button> ButtonBuilder::WeaponCard(double x, double y, double width, double height, const std::string& id, int dmg, int firerate, int price, const std::string& weaponIconTextureName)
{
	const double textScale = width / 700.0;

	Button card(x, y, width, height, 0, 0, width, height, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".0" }, { Button::Status::CLICKED, ".0" }});
	
	double widthWeaponIcon = width / 6.0;
	double heightWeaponIcon = height * 0.8;
	double weaponIconOffsetX = x + width / 15.0;

	Button weaponIcon(weaponIconOffsetX, y + (height - heightWeaponIcon) * 0.5, widthWeaponIcon, heightWeaponIcon, 0, 0, widthWeaponIcon, heightWeaponIcon, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, weaponIconTextureName}, { Button::Status::HOVERED, weaponIconTextureName }, { Button::Status::CLICKED, weaponIconTextureName }});

	double weaponInfoOffsetX = weaponIconOffsetX + widthWeaponIcon + width / 15.0;
	double weaponInfoWidth = width / 6.0;
	double weaponInfoHeight = height / 4.0;
	double fireratePaddingLeft = width / 15;
	double firerateOffsetX = weaponInfoOffsetX + fireratePaddingLeft + weaponInfoWidth;

	std::string damageStr = "Damage: " + std::to_string(dmg);
	std::string firerateStr = "Firerate: " + std::to_string(firerate);

	Button dmgInfo(weaponInfoOffsetX, y + (height - weaponInfoHeight) * 0.5, weaponInfoWidth, weaponInfoHeight, 0, 0, weaponInfoWidth, weaponInfoHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, {Button::Status::HOVERED, ".0"}, {Button::Status::CLICKED, ".0"}}, damageStr, 0.0, textScale);
	Button firerateInfo(firerateOffsetX, y + (height - weaponInfoHeight) * 0.5, weaponInfoWidth, weaponInfoHeight, 0, 0, weaponInfoWidth, weaponInfoHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".0" }, { Button::Status::CLICKED, ".0" }}, firerateStr, 0.0, textScale);

	double buyOffsetX = firerateOffsetX + weaponInfoWidth + width / 15.0;
	double buyWidth = width / 6.0;
	double buyHeight = height / 5.0;

	std::string buyStr = std::to_string(price) + " G";

	Button buy(buyOffsetX, y + (height - buyHeight) * 0.5, buyWidth, buyHeight, 0, 0, buyWidth, buyHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, buyStr, 0.0, textScale);


	std::map<std::string, Button> buttons{
		{id + "_0_card", card},
		{id + "_1_weaponIcon", weaponIcon},
		{id + "_1_dmgInfo", dmgInfo},
		{id + "_1_firerateInfo", firerateInfo},
		{id + "_1_buy", buy}
	};

	return buttons;
}


std::map<std::string, Button> ButtonBuilder::ShopTabsButtons(double x, double y, double totalWidth, double totalHeight, const std::vector<std::string>& texturesWeapons, const std::vector<std::string>& texturesBullets, const std::vector<std::string>& texturesHealthArmor)
{
	if (texturesWeapons.size() < 3 || texturesBullets.size() < 3 || texturesHealthArmor.size() < 3)
		throw std::runtime_error("Tab buttons builder: not enough textures\n");


	double scale = 1.0;

	std::string weaponsStr = "Weapons";
	std::string bulletsStr = "Bullets";
	std::string healthArmorStr = "Health/Armor";

	std::string font = "Antonio";

	double maxWidth = std::max({ TextRenderer::get().getTextWidth(ResourceManager::getFont(font), scale, weaponsStr),
								 TextRenderer::get().getTextWidth(ResourceManager::getFont(font), scale, bulletsStr),
								 TextRenderer::get().getTextWidth(ResourceManager::getFont(font), scale, healthArmorStr) });

	double paddnigLeftAndRight = 20;

	double buttonWidth = maxWidth + 2 * paddnigLeftAndRight;
	double buttonHeight = totalHeight;

	double WeaponsTabButtonX = x + (totalWidth - 3 * buttonWidth) / 2.0;

	Button WeaponsTabButton(WeaponsTabButtonX, y, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, texturesWeapons[0]}, {Button::Status::HOVERED, texturesWeapons[1]}, {Button::Status::CLICKED, texturesWeapons[2] }}, weaponsStr, 0, scale, font, true);

	double BulletsTabButtonX = WeaponsTabButtonX + buttonWidth;

	Button BulletsTabButton(BulletsTabButtonX, y, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, texturesBullets[0]}, {Button::Status::HOVERED, texturesBullets[1] }, {Button::Status::CLICKED, texturesBullets[2] }}, bulletsStr, 0, scale, font, true);

	double HealthArmorTabButtonX = BulletsTabButtonX + buttonWidth;

	Button HealthArmorTabButton(HealthArmorTabButtonX, y, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, texturesHealthArmor[0]}, {Button::Status::HOVERED, texturesHealthArmor[1] }, {Button::Status::CLICKED, texturesHealthArmor[2] }}, healthArmorStr, 0, scale, font, true);

	std::map<std::string, Button> buttons{
		{weaponsStr, WeaponsTabButton},
		{bulletsStr, BulletsTabButton},
		{healthArmorStr, HealthArmorTabButton}
	};

	return buttons;
}

std::vector<std::vector<std::string>> ButtonBuilder::tabTexturesWeaponsSelected()
{
	return std::vector<std::vector<std::string>> {
		{ "tab3", "tab3", "tab3" },
		{ "tab1", "tab2", "tab3" },
		{ "tab1", "tab2", "tab3" }
	};
}

std::vector<std::vector<std::string>> ButtonBuilder::tabTexturesBulletsSelected()
{
	return std::vector<std::vector<std::string>> {
		{ "tab1", "tab2", "tab3" },
		{ "tab3", "tab3", "tab3" },
		{ "tab1", "tab2", "tab3" }
	};
}

std::vector<std::vector<std::string>> ButtonBuilder::tabTexturesHealthArmorSelected()
{
	return std::vector<std::vector<std::string>> {
		{ "tab1", "tab2", "tab3" },
		{ "tab1", "tab2", "tab3" },
		{ "tab3", "tab3", "tab3" }
	};
}



std::map<std::string, Button> ButtonBuilder::ShopTitleCard(double x, double y, double totalWidth, double totalHeight)
{
	double scale = 1.0;

	std::string titleStr = "Shop";
	
	std::string font = "Antonio";

	double paddnigLeftAndRight = 120;

	double buttonWidth = TextRenderer::get().getTextWidth(ResourceManager::getFont(font), scale, titleStr) + 2 * paddnigLeftAndRight;
	double buttonHeight = totalHeight;

	double titleX = x + (totalWidth - buttonWidth) / 2.0;

	Button TitleButton(titleX, y, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, titleStr, 0, scale, font, true);

	std::map<std::string, Button> buttons{ {titleStr, TitleButton} };

	return buttons;

}

