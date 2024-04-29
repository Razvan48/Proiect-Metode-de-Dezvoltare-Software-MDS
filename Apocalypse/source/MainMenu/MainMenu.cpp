#include "MainMenu.h"
#include "../WindowManager/WindowManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>
#include "../Input/InputHandler.h"
#include "../Map/Map.h"
#include "../Entity/Player/Player.h"
#include "../HUD/HUDManager.h"



MainMenu::MainMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	buttonWidth(drawWidth * 0.75),
	buttonHeight(drawHeight * 0.1),
	buttons(std::map<std::string, Button>{
		{ "quit", Button(getButtonPosX(), getButtonPosY(0), buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "Quit")},
		{ "play", Button(getButtonPosX(), getButtonPosY(1), buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "Play") },
		{ "settings", Button(getButtonPosX(), getButtonPosY(2), buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "Settings") }
})
{	
	buttons.setFunctions(
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), MainMenu::hoverAnyButton }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), MainMenu::hoverLostAnyButton }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} },
		{ "play", [](Button&) {
			MainMenu::get().isInGame = true;
			InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());
		} } }
	);

}


MainMenu& MainMenu::get()
{
	double dW = WindowManager::get().getWindowWidth(); //  *0.75;
	double dH = WindowManager::get().getWindowHeight();
	double x = 0;
	double y = 0;


	static MainMenu instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}

void MainMenu::draw()
{
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName2D), glm::vec2(x, y), glm::vec2(drawWidth, drawHeight), 0);

	buttons.draw();

}

double MainMenu::getButtonPosX() {
	return x + WindowManager::get().getWindowWidth() / 2.0 - drawWidth / 2 + buttonOffsetX;
	// return  buttonOffsetX;
}

double MainMenu::getButtonPosY(int index) {
	return -y + WindowManager::get().getWindowHeight() / 2.0 - drawHeight / 2 + buttonOffsetY + index * (buttonHeight + spaceAfterButton);
	// return drawHeight / 2.0 - buttonOffsetY - buttonHeight / 2.0 - index * (buttonHeight + spaceAfterButton);
}


void MainMenu::setupMainMenuInputComponent()
{
	buttons.activate();
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


void MainMenu::hoverAnyButton(Button& button)
{
	button.setHovered();
	button.setLabel(toUpper(button.getLabel()));
}

void MainMenu::hoverLostAnyButton(Button& button)
{
	button.setDefault();
	button.setLabel(initCap(button.getLabel()));
}
