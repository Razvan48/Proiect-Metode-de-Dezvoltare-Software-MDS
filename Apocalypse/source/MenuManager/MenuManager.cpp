#include "MenuManager.h"
#include "../Input/InputHandler.h"


MenuManager& MenuManager::get()
{
	static MenuManager instance;
	return instance;
}

void MenuManager::pop() {
	if (!menuStack.empty())
	{
		if (menuStack.size() > 1)
			menuStack[menuStack.size() - 2]->setIsInMenu(true);
		menuStack[menuStack.size() - 1]->setIsInMenu(false);
	}
	menuStack.pop_back(); 
	if (!menuStack.empty())
	{
		menuStack[menuStack.size() - 1]->setIsInMenu(true);
		menuStack[menuStack.size() - 1]->setupInputComponent();
	}
}

void MenuManager::push(MenuBase& m) { 
	if (!menuStack.empty())
	{
		m.setIsInMenu(true);
		menuStack[menuStack.size() - 1]->setIsInMenu(false);
	}
	menuStack.push_back(&m); 
	menuStack[menuStack.size() - 1]->setIsInMenu(true);
	menuStack[menuStack.size() - 1]->setupInputComponent();
}

MenuBase& MenuManager::top() const
{
	// std::cout << this->size() << "\n";
	if (menuStack.empty())
	{
		InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());

		throw noMenuOpened();
	}

	return *menuStack[menuStack.size() - 1];
}

void MenuManager::clear()
{
	while (!menuStack.empty())
		this->pop();
}

void MenuManager::draw() const
{
	for (auto& i : menuStack)
		i->draw();
}

void MenuManager::play()
{
	while (MenuManager::size())
		if (MenuManager::top().getIsInMenu() == true)
			MenuManager::top().playMenu();
		else
			std::cout << "getIsInMenu == false\n";
}