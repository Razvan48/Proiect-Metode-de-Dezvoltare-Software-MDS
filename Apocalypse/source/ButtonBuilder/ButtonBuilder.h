#pragma once
#include "../Entity/Button/Button.h"

class ButtonBuilder
{
public:
	static Button backButton(double x = 0, double y = 0);
	static void backButtonClickFunction(Button& button);
};