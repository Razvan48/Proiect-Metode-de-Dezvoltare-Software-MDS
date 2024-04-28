#pragma once

#include <cctype>

#include "../Entity/TexturableEntity.h"
#include "../Entity/Button/Button.h"
#include "../ButtonGroup/ButtonGroup.h"

class PauseMenu : public virtual TexturableEntity
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
	PauseMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	PauseMenu(const std::string& textureName2D);
	~PauseMenu() = default;
	PauseMenu(const PauseMenu& other) = delete;
	PauseMenu& operator=(const PauseMenu& other) = delete;
	PauseMenu(const PauseMenu&& other) = delete;
	PauseMenu& operator=(const PauseMenu&& other) = delete;

protected:
	static std::string toUpper(const std::string& s);
	static std::string toLower(const std::string& s);
	static std::string initCap(const std::string& s);

public:
	static PauseMenu& get();
	void draw() override;

	void setupPauseMenuInputComponent();

	bool getIsInGame() const { return isInGame; }

	void playMenu();

	static void hoverAnyButton(Button& button);
	static void hoverLostAnyButton(Button& button);

};

