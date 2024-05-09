#pragma once

#include <iostream>
#include <stack>
#include <exception>

#include "MenuBase/MenuBase.h"


class noMenuOpened : public std::runtime_error
{
public:
	noMenuOpened(const std::string& msg = "") :runtime_error(msg) {}
};

class MenuManager
{
	std::stack<MenuBase*> menuStack;

public:
	
	static MenuManager& get();

	MenuBase& top() const;

	void pop();

	void push(MenuBase& m);

};

