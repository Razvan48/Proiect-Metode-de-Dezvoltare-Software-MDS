#include "Entity.h"

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

Entity::Entity(double x, double y, const std::string textureName, double drawWidth, double drawHeight) :
	x(x), y(y), textureName(textureName), drawWidth(drawWidth), drawHeight(drawHeight)
{

}

void Entity::draw()
{
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName), glm::vec2(this->x, this->y), glm::vec2(this->drawWidth, this->drawHeight));
}

Entity::~Entity()
{

}