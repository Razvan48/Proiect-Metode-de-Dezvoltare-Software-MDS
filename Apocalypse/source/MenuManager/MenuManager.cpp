#include "MenuManager.h"
#include "../Input/InputHandler.h"


MenuManager& MenuManager::get()
{
	static MenuManager instance;
	return instance;
}

void MenuManager::pop() {
	if (!menuStack.empty())
		menuStack.top()->setIsInMenu(false);
	menuStack.pop(); 
	if (!menuStack.empty())
	{
		menuStack.top()->setIsInMenu(true);
		menuStack.top()->setupInputComponent();
	}
}

void MenuManager::push(MenuBase& m) { 
	menuStack.push(&m); 
	menuStack.top()->setIsInMenu(true);
	menuStack.top()->setupInputComponent();
}

MenuBase& MenuManager::top() const
{
	if (menuStack.empty())
	{
		InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());
		throw noMenuOpened();
	}

	return *menuStack.top();
}


