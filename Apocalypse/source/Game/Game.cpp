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
#include "../InteractionManager/InteractionManager.h"
#include "../HUD/HUDManager.h"

#include <iostream>
#include "../MainMenu/MainMenu.h"

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
        // Floors
        ResourceManager::loadTexture("resources/textures/floors/.0.png", true, ".0");
        ResourceManager::loadTexture("resources/textures/floors/.1.png", true, ".1");
        ResourceManager::loadTexture("resources/textures/floors/.2.png", true, ".2");
        ResourceManager::loadTexture("resources/textures/floors/.3.png", true, ".3");
        ResourceManager::loadTexture("resources/textures/floors/.4.png", true, ".4");
        ResourceManager::loadTexture("resources/textures/floors/.5.png", true, ".5");
        ResourceManager::loadTexture("resources/textures/floors/.6.png", true, ".6");
        ResourceManager::loadTexture("resources/textures/floors/.7.png", true, ".7");
        ResourceManager::loadTexture("resources/textures/floors/.8.png", true, ".8");
        ResourceManager::loadTexture("resources/textures/floors/.9.png", true, ".9");
        ResourceManager::loadTexture("resources/textures/floors/.a.png", true, ".a");

        // Walls
        ResourceManager::loadTexture("resources/textures/walls/M0.png", true, "M0");
        ResourceManager::loadTexture("resources/textures/walls/M1.png", true, "M1");
        ResourceManager::loadTexture("resources/textures/walls/M2.png", true, "M2");

        // Frames
        ResourceManager::loadTexture("resources/textures/hud/weaponFrame.png", true, "weaponFrame");
        ResourceManager::loadTexture("resources/textures/hud/healthFrame.png", true, "healthFrame");
        ResourceManager::loadTexture("resources/textures/hud/staminaFrame.png", true, "staminaFrame");
        ResourceManager::loadTexture("resources/textures/hud/armorFrame.png", true, "armorFrame");

        ResourceManager::loadTexture("resources/textures/hud/red.png", false, "redBar");
        ResourceManager::loadTexture("resources/textures/hud/green.png", false, "greenBar");
        ResourceManager::loadTexture("resources/textures/hud/blue.png", false, "blueBar");

        // Weapons
        ResourceManager::loadTexture("resources/textures/hud/fist0.png", true, "fist0");
        ResourceManager::loadTexture("resources/textures/hud/knife0.png", true, "knife0");
        ResourceManager::loadTexture("resources/textures/hud/pistol0.png", true, "pistol0");
        ResourceManager::loadTexture("resources/textures/hud/grenade0.png", true, "grenade0");
        ResourceManager::loadTexture("resources/textures/hud/shotgun0.png", true, "shotgun0");
        ResourceManager::loadTexture("resources/textures/hud/automated0.png", true, "automated0");
        ResourceManager::loadTexture("resources/textures/hud/automated1.png", true, "automated1");
        ResourceManager::loadTexture("resources/textures/hud/minigun0.png", true, "minigun0");

        // Bullets
        ResourceManager::loadTexture("resources/textures/bullets/bullet0.png", true, "bullet0");
        ResourceManager::loadTexture("resources/textures/bullets/bullet1.png", true, "bullet1");
        ResourceManager::loadTexture("resources/textures/bullets/bullet2.png", true, "bullet2");
        ResourceManager::loadTexture("resources/textures/bullets/bullet3.png", true, "bullet3");

        // Shops
        ResourceManager::loadTexture("resources/textures/shops/shop0.png", true, "shop0");
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
        // Player Animations
        ResourceManager::loadFlipbook("resources/animations/playerIdle", 15.0f, "playerIdle");
        ResourceManager::loadFlipbook("resources/animations/playerWalking", 25.0f, "playerWalking");
        ResourceManager::loadFlipbook("resources/animations/playerRunning", 30.0f, "playerRunning");
        ResourceManager::loadFlipbook("resources/animations/playerTired", 10.0f, "playerTired");

        // Environment Animations
        ResourceManager::loadFlipbook("resources/animations/grenadeExplosion", 40.0f, "grenadeExplosion");
        ResourceManager::loadFlipbook("resources/animations/bulletBlast", 40.0f, "bulletBlast");

        // Doors
        ResourceManager::loadFlipbook("resources/animations/doorStatic0", 10.0f, "doorStatic0");
        ResourceManager::loadFlipbook("resources/animations/doorStatic1", 10.0f, "doorStatic1");

        ResourceManager::loadFlipbook("resources/animations/doorOpening0", 5.0f, "doorOpening0");
        ResourceManager::loadFlipbook("resources/animations/doorOpening1", 5.0f, "doorOpening1");
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

    // Load Entities
    this->entities.emplace_back(new Door(7.5, 14.5, 1.0, 1.0, 90.0, 0.0, 1.0, 1.0, 
        {
            { AnimatedEntity::EntityStatus::IDLE, "doorStatic0"},
            {AnimatedEntity::EntityStatus::OPENED, "doorOpening0"}
        }, 2.0, 2.0, 0)); // usa (doar sa testam) (usa gratis, cost 0)
    this->entities.emplace_back(new Door(7.5, 16.5, 1.0, 1.0, 90.0, 0.0, 1.0, 1.0,
        {
            { AnimatedEntity::EntityStatus::IDLE, "doorStatic1"},
            {AnimatedEntity::EntityStatus::OPENED, "doorOpening1"}
        }, 2.0, 2.0, 0)); // usa (doar sa testam) (usa gratis, cost 0)

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
    MainMenu::get().setupMainMenuInputComponent();
    for (int i = 0; i < this->entities.size(); ++i)
        if (std::dynamic_pointer_cast<Door>(this->entities[i]) != nullptr) // doar pentru usi momentan
            std::dynamic_pointer_cast<Door>(this->entities[i])->setupPlayerInputComponent(); // TODO: am numit corect functia?

    // SetupInput
    InputHandler::setInputComponent(InputHandler::getMenuInputComponent());

    while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
    {
        // Input
        InputHandler::update();

        // Collision System
        CollisionManager::get().handleCollisions(this->entities);

        // Interactions System
        InteractionManager::get().handleInteractions(this->entities);

        // Updates
        Camera::get().update();
        Player::get().update();

        // Render
        glClearColor(0.733f, 0.024f, 0.259f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Map
        Map::get().draw();

        // Game Entities
        this->drawEntities();

        // Player
        Player::get().draw();

        // HUD
        HUDManager::get().draw();

        MainMenu::get().playMenu();

        // Update Entities
        this->updateEntities(); // TODO: asta presupune ca entitatile tinute in vector-ul din clasa game nu isi mai dau update altundeva decat aici

        // Update/Tick
        GlobalClock::get().updateTime();

        // Swap the screen buffers
        glfwSwapBuffers(WindowManager::get().getWindow());
       
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }
}

void Game::updateEntities()
{
    for (int i = 0; i < this->entities.size(); ++i)
        this->entities[i]->update();
}

void Game::drawEntities()
{
    for (int i = 0; i < this->entities.size(); ++i)
        this->entities[i]->draw();
}

