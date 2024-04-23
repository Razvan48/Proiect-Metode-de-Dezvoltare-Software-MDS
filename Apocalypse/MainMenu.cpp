#include "MainMenu.h"
#include "source/WindowManager/WindowManager.h"
#include "source/Renderer/SpriteRenderer.h"
#include "source/ResourceManager/ResourceManager.h"
#include "EntityStatus.h"
#include <iostream>
#include "source/Input/InputHandler.h"
#include "source/Map/Map.h"
#include "source/Entity/Player/Player.h"
#include "source/HUD/HUDManager.h"


MainMenu::MainMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	buttonWidth(drawWidth * 0.75),
	buttonHeight(drawHeight * 0.1),
	quit(0, 0, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<AnimatedEntity::EntityStatus, std::string>()),
	play(0, 0, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<AnimatedEntity::EntityStatus, std::string>()),
	settings(0, 0, buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<AnimatedEntity::EntityStatus, std::string>())
{
	quit.setLabel("Quit");
	play.setLabel("Play");
	settings.setLabel("Settings");

	quit.setX(getButtonPosX());
	play.setX(getButtonPosX());
	settings.setX(getButtonPosX());

	quit.setY(getButtonPosY(0));
	play.setY(getButtonPosY(1));
	settings.setY(getButtonPosY(2));

}


MainMenu& MainMenu::get()
{
	double dW = WindowManager::get().getWindowWidth() * 0.75;
	double dH = WindowManager::get().getWindowHeight();
	double x = 0;
	double y = 0;


	static MainMenu instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}

void MainMenu::draw()
{
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName2D), glm::vec2(x, y), glm::vec2(drawWidth, drawHeight), 0);

	quit.draw();
	play.draw();
	settings.draw();
}

double MainMenu::getButtonPosX() { return x + buttonOffsetX; }
double MainMenu::getButtonPosY(int index) { return y + buttonOffsetY + index * (buttonHeight + spaceAfterButton); }


void MainMenu::setupMainMenuInputComponent()
{
	InputHandler::getMenuInputComponent().bindAxis(std::bind(&MainMenu::onPlayClick, this, std::placeholders::_1, std::placeholders::_2));
	InputHandler::getMenuInputComponent().bindAction("CLICK_PLAY", InputEvent::IE_Pressed, std::bind(&MainMenu::clickPlay, this));

}

void MainMenu::onPlayClick(double x, double y) // TODO: pentru celelalte butoane
{
	hoverPlay = hoverBox(x, y, play.getX(), play.getY(), play.getCollideWidth(), play.getCollideHeight());
	if (hoverPlay)
		play.setLabel(toUpper(play.getLabel()));
	else
		play.setLabel(initCap(play.getLabel()));
}

bool MainMenu::hoverBox(double mouseX, double mouseY, double x, double y, double width, double height)
{
	// std::cout << "box: " << x << " " << x + width << " " << "\n" << y << " " << y + height << "\n";

	// std::cout << "Play buton: " << play.getX() << " " << play.getX() + play.getCollideWidth() << "\n" << play.getY() << " " << play.getY() +  play.getCollideHeight() << "\n";

	// std::cout << "Mouse: " << mouseX << " " << mouseY << "\n";

	return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
		
}

void MainMenu::playMenu()
{
	while (isInGame == false && !glfwWindowShouldClose(WindowManager::get().getWindow()))
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

void MainMenu::clickPlay()
{
	if (hoverPlay)
	{
		isInGame = true;
		InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());
	}

}

std::string MainMenu::toUpper(const std::string& s)
{
	std::string rez = s;
	for (size_t i = 0; i < rez.size(); ++i)
		rez[i] = toupper(rez[i]);

	return rez;
}

std::string MainMenu::toLower(const std::string& s)
{
	std::string rez = s;
	for (size_t i = 0; i < rez.size(); ++i)
		rez[i] = tolower(rez[i]);

	return rez;
}

std::string MainMenu::initCap(const std::string& s)
{
	std::string rez = toLower(s);
	if (rez.size())
		rez[0] = toupper(rez[0]);

	return rez;
}

