#include "HUDManager.h"

#include "../ResourceManager/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../Renderer/TextRenderer.h"
#include "../Entity/Player/Player.h"

#include <string>

HUDManager& HUDManager::get()
{
	static HUDManager instance;
	return instance;
}

void HUDManager::draw()
{
	// top-left
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("healthFrame"), glm::vec2(-448.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
	int health = static_cast<int>(Player::get().getHealth());
	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(health), 50.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("staminaFrame"), glm::vec2(-320.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
	int stamina = static_cast<int>(Player::get().getStamina());
	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(stamina), 150.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("armorFrame"), glm::vec2(-192.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
	int armor = static_cast<int>(Player::get().getArmor());
	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(armor), 300.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	// top-right
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("fist0"), glm::vec2(448.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
	// SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("pistol0"), glm::vec2(448.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("weaponFrame"), glm::vec2(448.0f, 384.0f), glm::vec2(128.0f, 128.0f), 0.0f);
}

