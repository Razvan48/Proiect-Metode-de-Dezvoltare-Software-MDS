#include "Game.h"

#include <iostream> // TODO: delete
#include <fstream>

#include <nlohmann/json.hpp>

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
#include "../MainMenu/MainMenu.h"
#include "../PauseMenu/PauseMenu.h"
#include "../SoundManager/SoundManager.h"

Game::Game()
{
    // TODO: trebuie? \/
    WindowManager::get();
}

Game::~Game()
{
    // TODO: default?
}

Game& Game::get()
{
    static Game instance;
    return instance;
}

void Game::loadResources()
{
    // Load JSON
    std::ifstream gameFile("config/game.json");
    nlohmann::json gameJSON;
    gameFile >> gameJSON;
    gameFile.close();

    // Load Shaders
    try
    {
        for (auto& [shaderName, shader] : gameJSON["shaders"].items())
        {
            std::string* vertex = new std::string(shader["vertex"].get<std::string>());
            std::string* fragment = new std::string(shader["fragment"].get<std::string>());
            std::string* geometry = shader["geometry"].is_null() ? nullptr : new std::string(shader["geometry"].get<std::string>());
        
            ResourceManager::loadShader(vertex->c_str(), fragment->c_str(), geometry ? geometry->c_str() : nullptr, shaderName);

            delete vertex;
            delete fragment;
            delete geometry;
        }
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
        for (auto& [textureName, texture] : gameJSON["textures"].items())
        {
            std::string file = texture["file"].get<std::string>();
            bool alpha = texture["alpha"].get<bool>();

            ResourceManager::loadTexture(file.c_str(), alpha, textureName);
        }
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
        for (auto& [flipbookName, flipbook] : gameJSON["flipbooks"].items())
        {
            std::string directory = flipbook["directory"].get<std::string>();
            double framesPerSecond = flipbook["framesPerSecond"].get<double>();
            bool loop = flipbook["loop"].get<bool>();

            ResourceManager::loadFlipbook(directory.c_str(), framesPerSecond, loop, flipbookName);
        }
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::FLIPBOOK: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::FLIPBOOK: other error" << std::endl;
    }

    // Load Sounds
    try
    {
        for (auto& [soundName, sound] : gameJSON["sounds"].items())
        {
            std::string file = sound["file"].get<std::string>();
            int mode = sound["mode"].get<int>();

            ResourceManager::loadSound(file.c_str(), mode, soundName);
        }
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::SOUND: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::SOUND: other error" << std::endl;
    }

    // Load Fonts
    try
    {
        for (auto& [fontName, font] : gameJSON["fonts"].items())
        {
            std::string file = font["file"].get<std::string>();
            int size = font["size"].get<int>();

            ResourceManager::loadFont(file.c_str(), size, fontName);
        }
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::FONT: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::FONT: other error" << std::endl;
    }

    // Load Map
    try
    {
        std::string file = gameJSON["map"].get<std::string>();

        Map::get().readMap(file);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::MAP: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::MAP: other error" << std::endl;
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
}

void Game::run()
{
    this->loadResources();

    // TODO: trebuie puse altundeva, iar atunci cand vom avea meniu trebuie pe false, nu true
    Camera::get().setFollowsPlayer(true);

    // TODO: de pus in constructor
    Player::get().setupPlayerInputComponent();
    MainMenu::get().setupMainMenuInputComponent();

    // Setup Input
    InputHandler::setInputComponent(InputHandler::getMenuInputComponent());

    // Setup Sound System
    SoundManager::get().play("walking", true);
    SoundManager::get().play("running", true);

    // TODO: test
    // Player::get().load();

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

        // Main Menu
        MainMenu::get().playMenu();
        PauseMenu::get().playMenu();

        // Update Entities
        this->updateEntities(); // TODO: asta presupune ca entitatile tinute in vector-ul din clasa game nu isi mai dau update altundeva decat aici

        // Update/Tick
        GlobalClock::get().updateTime();

        // Swap the screen buffers
        glfwSwapBuffers(WindowManager::get().getWindow());
       
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }

    // TODO: test
    Player::get().save();
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

