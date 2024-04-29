#pragma once

#include <cctype>

#include "../Entity/TexturableEntity.h"
#include "../Entity/Button/Button.h"
#include "../ButtonGroup/ButtonGroup.h"

class MainMenu : public virtual TexturableEntity
{
private:
	
	double buttonWidth;
	double buttonHeight;

	double buttonOffsetX = 200;
	double buttonOffsetY = 100;
	double spaceAfterButton = 5;

	ButtonGroup buttons;

	double getButtonPosX();
	double getButtonPosY(int index = 0);

	bool isInGame = false;

private:
	MainMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	MainMenu(const std::string& textureName2D); 
	~MainMenu() = default;
	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu(const MainMenu&& other) = delete;
	MainMenu& operator=(const MainMenu&& other) = delete;


protected:
	static std::string toUpper(const std::string& s);
	static std::string toLower(const std::string& s);
	static std::string initCap(const std::string& s);

public:
	static MainMenu& get();
	void draw() override;

	void setupMainMenuInputComponent();

	bool getIsInGame() const { return isInGame; }

	void playMenu();

	static void hoverAnyButton(Button& button);
	static void hoverLostAnyButton(Button& button);

};

