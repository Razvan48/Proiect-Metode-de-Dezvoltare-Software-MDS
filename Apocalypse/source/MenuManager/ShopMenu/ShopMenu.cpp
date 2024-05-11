#include "ShopMenu.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Input/InputHandler.h"
#include "../../Map/Map.h"
#include "../../Entity/Player/Player.h"
#include "../../HUD/HUDManager.h"
#include "../MenuManager.h"


// Shop menu abstract

ShopMenuAbstract::ShopMenuAbstract(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	MenuBase(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D, drawWidth / 9.0 * 7, drawHeight / 9.0),
	buttons()
{
	
}

double ShopMenuAbstract::getCardPosX() {
	return getButtonCoordsX() + buttonOffsetX;
}

double ShopMenuAbstract::getCardPosY(int index) {
	return getButtonCoordsY() + buttonOffsetY + index * (buttonHeight + spaceAfterButton);
}

void ShopMenuAbstract::draw()
{
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName2D), glm::vec2(x, y), glm::vec2(drawWidth, drawHeight), 0);

	buttons.draw();
}


void ShopMenuAbstract::setupInputComponent()
{
	buttons.activate();
}

void ShopMenuAbstract::playMenu()
{
	while (isInMenu == true && !glfwWindowShouldClose(WindowManager::get().getWindow()))
	{

		InputHandler::update();

		// Map
		Map::get().draw();

		// Player
		Player::get().draw();

		// HUD
		HUDManager::get().draw();

		draw();



		GlobalClock::get().updateTime();

		// Swap the screen buffers
		glfwSwapBuffers(WindowManager::get().getWindow());

		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
	}
}




// Weapons tab

ShopMenuWeapons::ShopMenuWeapons(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	MenuBase(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D, drawWidth / 9.0 * 7, drawHeight / 9.0),
	ShopMenuAbstract(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D)
{
	isInMenu = false;

	// auto allButtons = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(0), buttonWidth, buttonHeight, "1", 10, 500, 250, ".0");
	auto allButtons = loadMenuItems();
	allButtons.insert({ "back", ButtonBuilder::backButton(getButtonCoordsX(), getButtonCoordsY()) });

	double tabsWidth = drawWidth;
	double tabsHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double tabsX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double tabsY = y + tabsHeight * 2.0;
	auto textures = ButtonBuilder::tabTexturesWeaponsSelected();
	auto tabs = ButtonBuilder::ShopTabsButtons(tabsX, tabsY, tabsWidth, tabsHeight, textures[0], textures[1], textures[2]);

	allButtons.insert(tabs.begin(), tabs.end());

	double titleWidth = drawWidth;
	double titleHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double titleX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double titleY = y + tabsHeight;
	auto title = ButtonBuilder::ShopTitleCard(titleX, titleY, titleWidth, titleHeight);

	allButtons.insert(title.begin(), title.end());

	buttons.setButtons(allButtons);

	buttons.setFunctions(
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} },
		{
			"1_1_buy", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
			}
		},
		{
			"back", ButtonBuilder::backButtonClickFunction
		},
		{
			"Bullets", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuBullets::get());
}
		},
		{
			"Health/Armor", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuHealthArmor::get());
}
		}
	}
	);
}

std::map<std::string, Button> ShopMenuWeapons::loadMenuItems()
{
	int id = 1;

	std::map<std::string, Button> rez;

	for (int i = 0;i < 3;i++)
	{
		auto card = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(id - 1), buttonWidth, buttonHeight, std::to_string(id), 10, 500, 250, ".0");
		rez.insert(card.begin(), card.end());
		
		id++;
	}

	return rez;
}

ShopMenuAbstract& ShopMenuWeapons::get()
{
	double dW = WindowManager::get().getWindowWidth() * 0.8;
	double dH = WindowManager::get().getWindowHeight() * 0.9;
	double x = 0;
	double y = (-WindowManager::get().getWindowHeight() + dH) / 2.0;


	static ShopMenuWeapons instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}




// Bullets tab

ShopMenuBullets::ShopMenuBullets(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	MenuBase(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D, drawWidth / 9.0 * 7, drawHeight / 9.0),
	ShopMenuAbstract(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D)
{
	isInMenu = false;

	// auto allButtons = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(2), buttonWidth, buttonHeight, "1", 10, 500, 250, ".0");
	auto allButtons = loadMenuItems();
	allButtons.insert({ "back", ButtonBuilder::backButton(getButtonCoordsX(), getButtonCoordsY()) });

	double tabsWidth = drawWidth;
	double tabsHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double tabsX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double tabsY = y + tabsHeight * 2.0;
	auto textures = ButtonBuilder::tabTexturesBulletsSelected();
	auto tabs = ButtonBuilder::ShopTabsButtons(tabsX, tabsY, tabsWidth, tabsHeight, textures[0], textures[1], textures[2]);

	allButtons.insert(tabs.begin(), tabs.end());

	double titleWidth = drawWidth;
	double titleHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double titleX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double titleY = y + tabsHeight;
	auto title = ButtonBuilder::ShopTitleCard(titleX, titleY, titleWidth, titleHeight);

	allButtons.insert(title.begin(), title.end());

	buttons.setButtons(allButtons);

	buttons.setFunctions(
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} },
		{
			"1_1_buy", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
			}
		},
		{
			"back", ButtonBuilder::backButtonClickFunction
		},
		{
			"Weapons", [](Button&) {
				// std::cout << "-------------------\n";
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuWeapons::get());
}
		},
		{
			"Health/Armor", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuHealthArmor::get());
}
		}
	}
	);
}

std::map<std::string, Button> ShopMenuBullets::loadMenuItems()
{
	int id = 1;

	std::map<std::string, Button> rez;

	for (int i = 0;i < 5;i++)
	{
		auto card = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(id - 1), buttonWidth, buttonHeight, std::to_string(id), 10, 500, 250, ".0");
		rez.insert(card.begin(), card.end());

		id++;
	}

	return rez;
}

ShopMenuAbstract& ShopMenuBullets::get()
{
	double dW = WindowManager::get().getWindowWidth() * 0.8;
	double dH = WindowManager::get().getWindowHeight() * 0.9;
	double x = 0;
	double y = (-WindowManager::get().getWindowHeight() + dH) / 2.0;


	static ShopMenuBullets instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}






// Health/Armor tab

ShopMenuHealthArmor::ShopMenuHealthArmor(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	MenuBase(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D, drawWidth / 9.0 * 7, drawHeight / 9.0),
	ShopMenuAbstract(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D)
{
	isInMenu = false;

	// auto allButtons = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(4), buttonWidth, buttonHeight, "1", 10, 500, 250, ".0");
	auto allButtons = loadMenuItems();
	allButtons.insert({ "back", ButtonBuilder::backButton(getButtonCoordsX(), getButtonCoordsY()) });

	double tabsWidth = drawWidth;
	double tabsHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double tabsX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double tabsY = y + tabsHeight * 2.0;
	auto textures = ButtonBuilder::tabTexturesHealthArmorSelected();
	auto tabs = ButtonBuilder::ShopTabsButtons(tabsX, tabsY, tabsWidth, tabsHeight, textures[0], textures[1], textures[2]);

	allButtons.insert(tabs.begin(), tabs.end());

	double titleWidth = drawWidth;
	double titleHeight = (WindowManager::get().getWindowHeight() - drawHeight) / 2.0;
	double titleX = x + (WindowManager::get().getWindowWidth() - drawWidth) / 2.0;
	double titleY = y + tabsHeight;
	auto title = ButtonBuilder::ShopTitleCard(titleX, titleY, titleWidth, titleHeight);

	allButtons.insert(title.begin(), title.end());

	buttons.setButtons(allButtons);

	buttons.setFunctions(
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} },
		{
			"1_1_buy", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
			}
		},
		{
			"back", ButtonBuilder::backButtonClickFunction
		},
		{
			"Weapons", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuWeapons::get());
}
		},
		{
			"Bullets", [](Button&) {
				ShopMenuWeapons::get().setIsInMenu(false);
				MenuManager::get().pop();
				MenuManager::get().push(ShopMenuBullets::get());
}
		}
	}
	);
}

std::map<std::string, Button> ShopMenuHealthArmor::loadMenuItems()
{
	int id = 1;

	std::map<std::string, Button> rez;

	for (int i = 0;i < 1;i++)
	{
		auto card = ButtonBuilder::WeaponCard(getCardPosX(), getCardPosY(id-1), buttonWidth, buttonHeight, std::to_string(id), 10, 500, 250, ".0");
		rez.insert(card.begin(), card.end());

		id++;
	}

	return rez;
}

ShopMenuAbstract& ShopMenuHealthArmor::get()
{
	double dW = WindowManager::get().getWindowWidth() * 0.8;
	double dH = WindowManager::get().getWindowHeight() * 0.9;
	double x = 0;
	double y = (-WindowManager::get().getWindowHeight() + dH) / 2.0;


	static ShopMenuHealthArmor instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}

