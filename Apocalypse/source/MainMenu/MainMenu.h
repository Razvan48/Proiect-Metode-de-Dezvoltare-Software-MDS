#pragma once

#include <cctype>

#include "../Entity/TexturableEntity.h"
#include "../Entity/Button/Button.h"

class MainMenu : public virtual TexturableEntity
{
private:
	
	double buttonWidth;
	double buttonHeight;
	Button quit;
	Button play;
	Button settings;

	double buttonOffsetX = 200;
	double buttonOffsetY = 100;
	double spaceAfterButton = 5;

	double getButtonPosX();
	double getButtonPosY(int index = 0);

	bool isInGame = false;
	bool hoverPlay = false;

private:
	MainMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	MainMenu(const std::string& textureName2D); 
	~MainMenu() = default;
	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu(const MainMenu&& other) = delete;
	MainMenu& operator=(const MainMenu&& other) = delete;

	bool hoverBox(double mouseX, double mouseY, double x, double y, double width, double height);

protected:
	std::string toUpper(const std::string& s);
	std::string toLower(const std::string& s);
	std::string initCap(const std::string& s);

public:
	static MainMenu& get();
	void draw() override;

	void setupMainMenuInputComponent();
	void onPlayClick(double x, double y);

	bool getIsInGame() const { return isInGame; }

	void playMenu();

	void clickPlay();

};

