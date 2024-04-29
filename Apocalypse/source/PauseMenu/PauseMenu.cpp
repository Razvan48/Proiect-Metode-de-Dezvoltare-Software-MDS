#include "PauseMenu.h"
#include "../WindowManager/WindowManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

#include <iostream>
#include "../Input/InputHandler.h"
#include "../Map/Map.h"
#include "../Entity/Player/Player.h"
#include "../HUD/HUDManager.h"



PauseMenu::PauseMenu(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	buttonWidth(drawWidth * 0.75),
	buttonHeight(drawHeight * 0.1),
	buttons(std::map<std::string, Button>{
		{ "quit", Button(getButtonPosX(), getButtonPosY(0), buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "Quit")},
		{ "continue", Button(getButtonPosX(), getButtonPosY(1), buttonWidth, buttonHeight, 0, 0, buttonWidth, buttonHeight, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "Continue") }
})
{
	buttons.setFunctions(
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), PauseMenu::hoverAnyButton }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), PauseMenu::hoverLostAnyButton }},
		std::map<std::string, std::function<void(Button&)>>{{ButtonGroup::getAny(), [](Button&) {} },
		{ "continue", [](Button&) {
			PauseMenu::get().isInGame = true;
			InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());
		} } }
	);
}


PauseMenu& PauseMenu::get()
{
	double dW = WindowManager::get().getWindowWidth() * 0.6;
	double dH = WindowManager::get().getWindowHeight()* 0.5;
	double x = 0;
	double y = 0;


	static PauseMenu instance(x, y, dW, dH, 0, 0, ".0");
	return instance;
}

void PauseMenu::draw()
{
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName2D), glm::vec2(x, y), glm::vec2(drawWidth, drawHeight), 0);

	buttons.draw();
}

double PauseMenu::getButtonPosX() {
	return x + WindowManager::get().getWindowWidth() / 2.0 - drawWidth / 2 + buttonOffsetX;
	// return  buttonOffsetX;
}

double PauseMenu::getButtonPosY(int index) {
	return -y + WindowManager::get().getWindowHeight() / 2.0 - drawHeight / 2 + buttonOffsetY + index * (buttonHeight + spaceAfterButton);
	// return drawHeight / 2.0 - buttonOffsetY - buttonHeight / 2.0 - index * (buttonHeight + spaceAfterButton);
}


void PauseMenu::setupPauseMenuInputComponent()
{
	buttons.activate();
}

void PauseMenu::playMenu()
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

std::string PauseMenu::toUpper(const std::string& s)
{
	std::string rez = s;
	for (size_t i = 0; i < rez.size(); ++i)
		rez[i] = toupper(rez[i]);

	return rez;
}

std::string PauseMenu::toLower(const std::string& s)
{
	std::string rez = s;
	for (size_t i = 0; i < rez.size(); ++i)
		rez[i] = tolower(rez[i]);

	return rez;
}

std::string PauseMenu::initCap(const std::string& s)
{
	std::string rez = toLower(s);
	if (rez.size())
		rez[0] = toupper(rez[0]);

	return rez;
}


void PauseMenu::hoverAnyButton(Button& button)
{
	button.setHovered();
	button.setLabel(toUpper(button.getLabel()));
}

void PauseMenu::hoverLostAnyButton(Button& button)
{
	button.setDefault();
	button.setLabel(initCap(button.getLabel()));
}
