#include "Button.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Renderer/TextRenderer.h"
#include <iostream>

Button::Button():Entity(0,0,0,0,0,0), CollidableEntity(0,0,0,0,0,0,0,0), AnimatedEntity(0,0,0,0,0,0, std::map<AnimatedEntity::EntityStatus, std::string>()), label("") {
	// std::cout << "-------- constructor default button --------------\n";
}

Button::Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::string& label_) : 
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	label(label_)
{
	// std::cout << "- constructor parametrizat button -\n";
}


Button::~Button()
{

}

void Button::onCollide(CollidableEntity& other, glm::vec2 overlap) {}

void Button::update() {}

void Button::draw()
{
	// AnimatedEntity::draw();

	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), label, x, y, 1.0f, glm::vec3(1.0f, 0.8745f, 0.0f));
}