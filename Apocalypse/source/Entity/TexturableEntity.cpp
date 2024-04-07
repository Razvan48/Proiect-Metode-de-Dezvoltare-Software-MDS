#include "TexturableEntity.h"

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

TexturableEntity::TexturableEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), textureName2D(textureName2D)
{

}

void TexturableEntity::draw()
{
	// TODO: is shader name "sprite"?
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(this->textureName2D), glm::vec2(this->x, this->y), glm::vec2(this->drawWidth, this->drawHeight), this->rotateAngle);
}

TexturableEntity::~TexturableEntity()
{

}