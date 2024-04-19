#include "Game.h"

#include "../WindowManager/WindowManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../Renderer/TextRenderer.h"
#include "../GlobalClock/GlobalClock.h"
#include "../Map/Map.h"
#include "../Input/InputHandler.h"
#include "../Entity/Player/Player.h"
#include "../Camera/Camera.h"
#include "../CollisionManager/CollisionManager.h"
#include "../HUD/HUDManager.h"

#include <iostream>

Game::Game()
{
    // TODO: trebuie? \/
    WindowManager::get();
}

Game::~Game()
{

}

Game& Game::get()
{
    static Game instance;
    return instance;
}

void Game::loadResources()
{
    // Load Shaders
    try
    {
        ResourceManager::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
        ResourceManager::loadShader("shaders/text.vert", "shaders/text.frag", nullptr, "text");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::SHADER: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::SHADER: other error" << std::endl;
    }

    // Load Textures
    try
    {
        // ResourceManager::loadTexture("textures/OpenGL-test.png", true, "OpenGL");

        // Floors
        ResourceManager::loadTexture("textures/floors/.0.png", true, ".0");
        ResourceManager::loadTexture("textures/floors/.1.png", true, ".1");
        ResourceManager::loadTexture("textures/floors/.2.png", true, ".2");
        ResourceManager::loadTexture("textures/floors/.3.png", true, ".3");
        ResourceManager::loadTexture("textures/floors/.4.png", true, ".4");
        ResourceManager::loadTexture("textures/floors/.5.png", true, ".5");
        ResourceManager::loadTexture("textures/floors/.6.png", true, ".6");
        ResourceManager::loadTexture("textures/floors/.7.png", true, ".7");
        ResourceManager::loadTexture("textures/floors/.8.png", true, ".8");
        ResourceManager::loadTexture("textures/floors/.9.png", true, ".9");
        ResourceManager::loadTexture("textures/floors/.a.png", true, ".a");

        // Walls
        ResourceManager::loadTexture("textures/walls/M0.png", true, "M0");
        ResourceManager::loadTexture("textures/walls/M1.png", true, "M1");
        ResourceManager::loadTexture("textures/walls/M2.png", true, "M2");

        // Frames
        ResourceManager::loadTexture("textures/hud/weaponFrame.png", true, "weaponFrame");
        ResourceManager::loadTexture("textures/hud/healthFrame.png", true, "healthFrame");
        ResourceManager::loadTexture("textures/hud/staminaFrame.png", true, "staminaFrame");
        ResourceManager::loadTexture("textures/hud/armorFrame.png", true, "armorFrame");

        ResourceManager::loadTexture("textures/hud/red.png", false, "redBar");
        ResourceManager::loadTexture("textures/hud/green.png", false, "greenBar");
        ResourceManager::loadTexture("textures/hud/blue.png", false, "blueBar");

        // Weapons
        ResourceManager::loadTexture("textures/hud/fist0.png", true, "fist0");
        ResourceManager::loadTexture("textures/hud/pistol0.png", true, "pistol0");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::TEXTURE: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::TEXTURE: other error" << std::endl;
    }

    // Load Flipbooks
    try
    {
        // ResourceManager::loadFlipbook("textures/Fire+Sparks", "fire");

        // Player Animations
        // TODO: sa putem seta cat dureaza un flipbook si apoi interpolam liniar
        ResourceManager::loadFlipbook("animations/playerIdle", "playerIdle");
        ResourceManager::loadFlipbook("animations/playerWalking", "playerWalking");
        ResourceManager::loadFlipbook("animations/playerRunning", "playerRunning");
        ResourceManager::loadFlipbook("animations/playerTired", "playerTired");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::FLIPBOOK: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::FLIPBOOK: other error" << std::endl;
    }

    // Load Fonts
    try
    {
        ResourceManager::loadFont("fonts/Antonio-Bold.ttf", 24, "Antonio");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::FONT: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::FONT: other error" << std::endl;
    }

    // Configure Shaders
    glm::mat4 projection = glm::ortho(-0.5f * static_cast<float>(WindowManager::get().getWindowWidth()), 0.5f * static_cast<float>(WindowManager::get().getWindowWidth()), -0.5f * static_cast<float>(WindowManager::get().getWindowHeight()), 0.5f * static_cast<float>(WindowManager::get().getWindowHeight()));
    ResourceManager::getShader("sprite").use().setInteger("sprite", 0);
    ResourceManager::getShader("sprite").use().setMatrix4("projection", projection);

    // top-left coordinate of the scene will be at (0, 0) and the bottom-right part of the screen is at coordinate (WINDOW_WIDTH, WINDOW_HEIGHT)
    glm::mat4 orho = glm::ortho(0.0f, static_cast<float>(WindowManager::get().getWindowWidth()), static_cast<float>(WindowManager::get().getWindowHeight()), 0.0f);
    ResourceManager::getShader("text").use().setMatrix4("projection", orho);
    ResourceManager::getShader("text").use().setInteger("text", 0);

    // Load Map
    try
    {
        Map::get().readMap("maps/sandbox.map");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::MAP: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::MAP: other error" << std::endl;
    }
}

void Game::run()
{
    this->loadResources();

    // TODO: trebuie puse altundeva, iar atunci cand vom avea meniu trebuie pe false, nu true
    Camera::get().setFollowsPlayer(true);

    // TODO: de pus in constructor
    Player::get().setupPlayerInputComponent();

    // SetupInput
    InputHandler::setInputComponent(InputHandler::getPlayerInputComponent());

    while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
    {
        // Input
        InputHandler::update();

        // Collision System
        CollisionManager::get().handleCollisions(this->entities);

        // Updates
        Camera::get().update();
        Player::get().update();

        // Render
        glClearColor(0.733f, 0.024f, 0.259f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Map
        Map::get().draw();

        // Player
        Player::get().draw();

        // HUD
        HUDManager::get().draw();

        // Sprite
        /*
        SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("OpenGL"), glm::vec2(0.0f, 0.0f), glm::vec2(1000.0f, 433.5f), 0.0f);
        SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture(".0"), glm::vec2(128.0f, 128.0f), glm::vec2(128.0f, 128.0f), 0.0f);
        */
        
        // Text
        /*
        TextRenderer::get().draw(ResourceManager::getShader("text"), ResourceManager::getFont("Antonio"), "Hello World!", 50.0f, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.6f));
        */

        // Flipbook
        /*
        SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook("fire").getTextureAtTime(GlobalClock::get().getCurrentTime()), glm::vec2(410.0f, 40.0f), glm::vec2(192.0f, 192.0f), 0.0f);
        // 112.0f Player size // 128.0f debug
        SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook("playerIdle").getTextureAtTime(GlobalClock::get().getCurrentTime()), glm::vec2(112.0f, 112.0f), glm::vec2(112.0f, 112.0f), 180.0f);
        */

        // Update/Tick
        GlobalClock::get().updateTime();

        // Swap the screen buffers
        glfwSwapBuffers(WindowManager::get().getWindow());
       
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }
}

