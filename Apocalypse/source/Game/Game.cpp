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
#include "../Entity/Enemy/Enemy.h"
#include "../Entity/AnimatedEntity.h"
#include "../Camera/Camera.h"
#include "../CollisionManager/CollisionManager.h"
#include "../InteractionManager/InteractionManager.h"
#include "../HUD/HUDManager.h"
#include "../MenuManager/MainMenu/MainMenu.h"
#include "../MenuManager/PauseMenu/PauseMenu.h"
#include "../SoundManager/SoundManager.h"
#include "../MenuManager/MenuManager.h"
#include "../WaveManager/WaveManager.h"
#include "../Entity/Bullet/ThrownGrenade.h"
#include "../Entity/Explosion/Explosion.h"

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
    // Doors
    std::map<AnimatedEntity::EntityStatus, std::string> m0 = {
        { AnimatedEntity::EntityStatus::IDLE, "doorStatic0"},
        { AnimatedEntity::EntityStatus::OPENED, "doorOpening0"}
    };
    std::vector<AnimatedEntity::EntityStatus> v0 = { AnimatedEntity::EntityStatus::IDLE };
    Map::get().addDoor(std::make_shared<Door>(8.5, 14.5, 1.0, 1.0, 90.0, 0.0, 1.0, 1.0, m0, v0, 2.0, 2.0, 0)); // usa (doar sa testam) (usa gratis, cost 0)
    std::map<AnimatedEntity::EntityStatus, std::string> m1 = {
        { AnimatedEntity::EntityStatus::IDLE, "doorStatic1"},
        { AnimatedEntity::EntityStatus::OPENED, "doorOpening1"}
    };
    std::vector<AnimatedEntity::EntityStatus> v1 = { AnimatedEntity::EntityStatus::IDLE };
    Map::get().addDoor(std::make_shared<Door>(8.5, 16.5, 1.0, 1.0, 90.0, 0.0, 1.0, 1.0, m1, v1, 2.0, 2.0, 100)); // usa (doar sa testam) // COST 100
    std::map<AnimatedEntity::EntityStatus, std::string> m2 = {
        { AnimatedEntity::EntityStatus::IDLE, "doorStatic1"},
        { AnimatedEntity::EntityStatus::OPENED, "doorOpening1"}
    };
    std::vector<AnimatedEntity::EntityStatus> v2 = { AnimatedEntity::EntityStatus::IDLE };
    Map::get().addDoor(std::make_shared<Door>(7.5, 8.5, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, m2, v2
    , 2.0, 2.0, 0)); // usa (doar sa testam) (usa gratis, cost 0)

    // Configure Shaders
    glm::mat4 projection = glm::ortho(-0.5f * static_cast<float>(WindowManager::get().getWindowWidth()), 0.5f * static_cast<float>(WindowManager::get().getWindowWidth()), -0.5f * static_cast<float>(WindowManager::get().getWindowHeight()), 0.5f * static_cast<float>(WindowManager::get().getWindowHeight()));
    ResourceManager::getShader("sprite").use().setInteger("sprite", 0);
    ResourceManager::getShader("sprite").use().setMatrix4("projection", projection);

    ResourceManager::getShader("player").use().setInteger("sprite", 0);
    ResourceManager::getShader("player").use().setMatrix4("projection", projection);

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

    // MainMenu::get().setupMainMenuInputComponent();
    MenuManager::get().push(MainMenu::get());

    // Setup Input
    InputHandler::setInputComponent(InputHandler::getMenuInputComponent());

    // Setup Sound System
    SoundManager::get().play("walking", true);
    SoundManager::get().play("running", true);
    SoundManager::get().play("tired", true);
    SoundManager::get().play("soundtrack", true);

    // TODO: test
    // Player::get().load();

    while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
    {
        // Update
        InputHandler::update(); // TODO: delete?
        Map::get().update();
        Camera::get().update();
        Player::get().update();
        this->updateEntities();

        // Collision System
        CollisionManager::get().handleCollisions(this->entities);

        // Interactions System
        InteractionManager::get().handleInteractions(this->entities);

        // Render
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Map // TODO: usile de mutat in Map
        Map::get().draw();

        // Game Entities
        // Dead Bodies
        this->drawDeadBodies();

        // Player
        Player::get().draw();

        // Entities
        this->drawEntities();

        // HUD
        HUDManager::get().draw();

        // Wave Manager
        WaveManager::get().update();

        // Main Menu
        try
        {
            MenuManager::get().top().playMenu();
        }
        catch (noMenuOpened& err) {   }

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
    {
        if (entities[i]->getDeleteEntity())
        {
            std::swap(entities[i], entities[entities.size() - 1]);
            entities.pop_back();
            --i;
        }
    }

    for (int i = 0; i < this->entities.size(); ++i)
        this->entities[i]->update();

    for (int i = 0; i < this->entities.size(); ++i)
    {
        if (std::dynamic_pointer_cast<Enemy>(entities[i]) &&
            (entities[i]->getX() - Player::get().getX()) * (entities[i]->getX() - Player::get().getX()) +
            (entities[i]->getY() - Player::get().getY()) * (entities[i]->getY() - Player::get().getY())
            <=
            std::dynamic_pointer_cast<Enemy>(entities[i])->getAttackRadius() * std::dynamic_pointer_cast<Enemy>(entities[i])->getAttackRadius())
        {
            Player::get().setHealth(std::max(0.0, Player::get().getHealth() - std::dynamic_pointer_cast<Enemy>(entities[i])->getAttackDamage()));
        }
    }
}

void Game::drawDeadBodies()
{
    for (int i = 0; i < this->deadBodies.size(); ++i)
        this->deadBodies[i]->draw();
}

void Game::drawEntities() // grenazile si exploziile la urma (sunt mai la inaltime)
{
    for (int i = 0; i < this->entities.size(); ++i)
    {
        if (std::dynamic_pointer_cast<ThrownGrenade>(this->entities[i]))
            continue;
        if (std::dynamic_pointer_cast<Explosion>(this->entities[i]))
            continue;

        this->entities[i]->draw();
    }

    for (int i = 0; i < this->entities.size(); ++i) // grenazi
        if (std::dynamic_pointer_cast<ThrownGrenade>(this->entities[i]))
            this->entities[i]->draw();

    for (int i = 0; i < this->entities.size(); ++i) // explozii
        if (std::dynamic_pointer_cast<Explosion>(this->entities[i]))
            this->entities[i]->draw();
}

void Game::addEntity(std::shared_ptr<Entity> const entity)
{
    this->entities.emplace_back(entity);
}

void Game::addDeadBody(std::shared_ptr<DeadBody> const deadBody)
{
    this->deadBodies.emplace_back(deadBody);
}

