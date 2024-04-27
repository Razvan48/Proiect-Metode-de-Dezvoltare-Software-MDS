#include "Button.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Renderer/TextRenderer.h"

Button::Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D) : 
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D)
{

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