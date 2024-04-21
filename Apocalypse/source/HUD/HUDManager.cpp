#include "HUDManager.h"

#include "../WindowManager/WindowManager.h"
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
	int numberOfTextures = 5;

	int widthOffset = 32;	// TODO: delete
	int heightOffset = 32;	// TODO: delete

	int textureScaleWidth = 32;
	int textureScaleHeight = 32;
	
	int width = -1 * WindowManager::get().getWindowWidth() / 2 + widthOffset;
	int height = WindowManager::get().getWindowHeight() / 2 - heightOffset;

	// health bar
	double fill = Player::get().getHealth() / Player::get().getHealthCap();
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("redBar"), glm::vec2(width - 16.0 + textureScaleWidth * numberOfTextures * fill / 2.0, height), glm::vec2(textureScaleWidth * numberOfTextures * fill, textureScaleHeight), 0.0f);

	for (int i = 0; i < numberOfTextures; i++)
	{
		SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("healthFrame"), glm::vec2(width + i * textureScaleWidth, height), glm::vec2(textureScaleWidth, textureScaleHeight), 0.0f);
	}

	//int health = static_cast<int>(Player::get().getHealth());
	//TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(health), 50.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	// stamina bar
	height -= 45;

	fill = Player::get().getStamina() / Player::get().getStaminaCap();
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("greenBar"), glm::vec2(width - 16.0 + textureScaleWidth * numberOfTextures * fill / 2.0, height), glm::vec2(textureScaleWidth * numberOfTextures * fill , textureScaleHeight), 0.0f);

	for (int i = 0; i < numberOfTextures; i++)
	{
		SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("staminaFrame"), glm::vec2(width + i * textureScaleWidth, height), glm::vec2(textureScaleWidth, textureScaleHeight), 0.0f);
	}

	//int stamina = static_cast<int>(Player::get().getStamina());
	//TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(stamina), 150.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	// armor bar
	height -= 45;

	fill = Player::get().getArmor() / Player::get().getArmorCap();
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("blueBar"), glm::vec2(width - 16.0 + textureScaleWidth * numberOfTextures * fill / 2.0, height), glm::vec2(textureScaleWidth * numberOfTextures * fill, textureScaleHeight), 0.0f);

	for (int i = 0; i < numberOfTextures; i++)
	{
		SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("armorFrame"), glm::vec2(width + i * textureScaleWidth, height), glm::vec2(textureScaleWidth, textureScaleHeight), 0.0f);
	}

	//int armor = static_cast<int>(Player::get().getArmor());
	//TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), std::to_string(armor), 300.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	// top-right
	textureScaleWidth = 128;
	textureScaleHeight = 128;

	width = WindowManager::get().getWindowWidth() / 2 - textureScaleWidth / 2;
	height = WindowManager::get().getWindowHeight() / 2 - textureScaleHeight / 2;

	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("fist0"), glm::vec2(width, height), glm::vec2(textureScaleWidth, textureScaleHeight), 0.0f);
	// SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("pistol0"), glm::vec2(width, height), glm::vec2(textureWidth, textureHeight, 0.0f);
	SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("weaponFrame"), glm::vec2(width, height), glm::vec2(textureScaleWidth, textureScaleHeight), 0.0f);

	width = WindowManager::get().getWindowWidth() - textureScaleWidth;
	height = textureScaleHeight + 10;

	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), "GOLD: 100", width, height, 1.0f, glm::vec3(1.0f, 0.8745f, 0.0f));

	// down-right
	width = WindowManager::get().getWindowWidth() - textureScaleWidth;
	height = WindowManager::get().getWindowHeight() - 64;

	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), "WAVE: 10", width, height, 1.0f, glm::vec3(1.0f, 0.098f, 0.0f));

	height -= 32;
	TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), "KILLS: 10", width, height, 1.0f, glm::vec3(1.0f, 0.098f, 0.0f));
}

