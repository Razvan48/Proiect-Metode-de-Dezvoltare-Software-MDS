#include "ButtonBuilder.h"
#include "../MenuManager/PauseMenu/PauseMenu.h"
#include "../MenuManager/MenuManager.h"


Button ButtonBuilder::backButton(double x, double y)
{
	return Button(x, y, 40, 40, 0, 0, 40, 40, std::map<Button::Status, std::string>{{Button::Status::DEFAULT, ".0"}, { Button::Status::HOVERED, ".1" }, { Button::Status::CLICKED, ".2" }}, "");
}

void ButtonBuilder::backButtonClickFunction(Button& button) {
	PauseMenu::get().setIsInMenu(false);
	MenuManager::get().pop();
}


