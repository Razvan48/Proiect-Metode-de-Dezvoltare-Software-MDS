#include "Game.h"

#include "../WindowManager/WindowManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../GlobalClock/GlobalClock.h"
#include "../Map/Map.h"

#include <iostream>

SpriteRenderer* Renderer;

Game::Game()
{
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
    // load shaders
    try
    {
        ResourceManager::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::TEXTURE: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::TEXTURE: other error" << std::endl;
    }

    // load textures
    try
    {
        ResourceManager::loadTexture("textures/OpenGL-test.png", true, "OpenGL");
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR::SHADER: " << err.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "ERROR::SHADER: other error" << std::endl;
    }

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WindowManager::get().getWindowWidth()), static_cast<float>(WindowManager::get().getWindowHeight()), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().setInteger("sprite", 0);
    ResourceManager::getShader("sprite").use().setMatrix4("projection", projection);

    // TODO: refactor
    Renderer = new SpriteRenderer();
}

void Game::run()
{
    this->loadResources();

    while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
    {
        // Input
        // TODO

        // Render
        glClearColor(0.733f, 0.024f, 0.259f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: refactor
        Renderer->draw(ResourceManager::getShader("sprite"), ResourceManager::getTexture("OpenGL"), glm::vec2(10.0f, 150.0f), glm::vec2(1000.0f, 433.5f), 0.0f);

        // Update
        GlobalClock::get().updateTime();

        // Swap the screen buffers
        glfwSwapBuffers(WindowManager::get().getWindow());
       
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
    }
}

